/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:54 by alex              #+#    #+#             */
/*   Updated: 2025/10/23 13:54:06 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **full_cmd, char *full_path, t_prompt prompt)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execute(full_cmd, full_path, prompt);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

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

int	pipex(t_prompt prompt)
{
	int		filein;
	int		fileout;
	t_cmd	*current_node;
	int		i;
	int		j;

	j = 0;
	i = 0;
	// if (prompt.cmds->heredoc == 1)
	// {
	// 	fileout = open_file(prompt->cmds->outfile, 0);
	// 	here_doc(prompt.cmds->outfile);
	// }
	if (prompt.cmds->append == 1)
		fileout = open_file(prompt.cmds->outfile, 0);
	else
	{
		while (prompt.cmds->outfile[i])
		{
			fileout = open_file(prompt.cmds->outfile[i], 1);
			if (prompt.cmds->outfile[i++] == NULL)
				break ;
			close(fileout);
			i++;
		}
		while (prompt.cmds->infile[j])
		{
			filein = open_file(prompt.cmds->infile[j], 2);
			if (prompt.cmds->infile[j++] == NULL)
				break;
			close(filein);
			j++;
		}
		
		dup2(filein, 0);
	}
	current_node = prompt.cmds;
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
		child_process(current_node->full_cmd, current_node->full_path, prompt);
	}
	dup2(fileout, 1);
	execute(current_node->full_cmd, current_node->full_path, prompt);
	usage();
}
