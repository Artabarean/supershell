/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:51:16 by alex              #+#    #+#             */
/*   Updated: 2025/10/20 13:14:28 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exec(char *cmd, char **envp, int term_fd)
{
	char	**cmd_com;
	char	*path;

	path = NULL;
	cmd_com = ft_split(cmd, ' ');
	if (!ft_strchr(cmd_com[0], '/'))
	{
		path = get_path(cmd_com[0], envp, cmd_com, term_fd);
		if (!path)
		{
			access(cmd_com[0], F_OK | X_OK);
			error_comm(cmd_com[0], cmd_com, term_fd);
		}
	}
	else
	{
		path = cmd_com[0];
		if (access(cmd_com[0], F_OK | X_OK) < 0)
			error_commfr(cmd_com[0], cmd_com, term_fd);
	}
	if (execve(path, &cmd_com[0], envp) == -1)
		error_commfr(cmd_com[0], cmd_com, term_fd);
	close(term_fd);
}

void	child(char **argv, char **envp, int *p_fd, int term_fd)
{
	int	infile;

	infile = open_file(argv[1], 0, p_fd);
	if (infile == -1)
	{
		error_filen(argv[1], p_fd);
		exit(0);
	}
	dup2(infile, 0);
	close(infile);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	close(p_fd[1]);
	exec(argv[2], envp, term_fd);
}

void	second_child(char **argv, int *p_fd, char **envp, int term_fd)
{
	int	outfile;

	outfile = open_file(argv[4], 1, p_fd);
	dup2(outfile, 1);
	close(outfile);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	close(p_fd[0]);
	exec(argv[3], envp, term_fd);
}

int	main(int argc, char *argv[], char **envp)
{
	int		p_fd[2];
	pid_t	*pid;
	int		term_fd;

	pid = malloc(sizeof(pid_t) * numoffds(argv));
	if (argc < 5)
		handle_exit();
	if (pipe(p_fd) == -1)
		exit(-1);
	pid[0] = fork();
	pid_check(pid[0]);
	term_fd = dup(1);
	if (pid[0] == 0)
		child(argv, envp, p_fd, term_fd);
	pid[1] = fork();
	pid_check(pid[1]);
	if (pid[1] == 0)
		second_child(argv, p_fd, envp, term_fd);
	waitpid(pid[0], NULL, 0);
	return (fd_closer(p_fd), 0);
}
