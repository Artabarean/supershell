/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:54 by alex              #+#    #+#             */
/*   Updated: 2025/10/29 11:43:51 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	here_doc(char *limiter)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
}

void	first_proc(t_cmd *curr_node , int filein, int fileout, t_prompt prompt)
{
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	if (filein != -1)
		fd[0] = filein;
	if (fileout != -1)
		fd[1] = fileout;
	prompt.pid = fork();
	if (prompt.pid == -1)
		error();
	if (prompt.pid == 0)
	{
		dup2(fd[1], 1);
		execute(curr_node->full_cmd, curr_node->full_path, prompt);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}

void	child_processmid(t_cmd *curr_node , t_prompt prompt)
{
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	prompt.pid = fork();
	if (prompt.pid == -1)
		error();
	if (prompt.pid == 0)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execute(curr_node->full_cmd, curr_node->full_path, prompt);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	child_procend(t_cmd *curr_node , int	filein, int fileout, t_prompt prompt)
{
	prompt.pid = fork();
	if (prompt.pid == -1)
		error();
	if (prompt.pid == 0)
	{
		if (fileout != -1)
			dup2(fileout, 1);
		execute(curr_node->full_cmd, curr_node->full_path, prompt);
	}
	else
	{
		if (fileout != -1)
			close(fileout);
		if (filein != -1)
			dup2(filein, 0);
	}
}

int	pipex(t_prompt prompt)
{
	int		filein;
	int		fileout;
	t_cmd	*current_node;
	int		last_status;
	int		status;

	filein = -1;
	fileout = -1;
	if (prompt.cmds->heredoc == 1)
	{
		fileout = open_file(prompt.cmds->outfile, 0);
		here_doc(prompt.cmds->outfile);
	}
	if (prompt.cmds->append == 1)
		fileout = open_file(prompt.cmds->outfile, 0);
	else
	{
		file_opener(prompt.cmds, fileout, filein);
		dup2(filein, 0);
	}
	current_node = prompt.cmds;
	childprocess_(current_node, filein, fileout, prompt);
	current_node = prompt.cmds;
	last_status = pid_stat(current_node ,prompt, status, last_status);
	check_status(last_status);
	return (0);
}
