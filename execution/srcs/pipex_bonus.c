/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:54 by alex              #+#    #+#             */
/*   Updated: 2025/10/24 12:24:47 by atabarea         ###   ########.fr       */
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

void	child_process1(t_cmd *current_node , int	filein, int fileout, t_prompt prompt)
{
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	if (filein != -1)
		fd[0] = filein;
	if (fileout != -1)
		fd[1] = fileout;
	current_node->pid = fork();
	if (current_node->pid == -1)
		error();
	if (current_node->pid == 0)
	{
		dup2(fd[1], 1);
		execute(current_node->full_cmd, current_node->full_path, prompt);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}

void	child_processmid(t_cmd *current_node , t_prompt prompt)
{
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	current_node->pid = fork();
	if (current_node->pid == -1)
		error();
	if (current_node->pid == 0)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execute(current_node->full_cmd, current_node->full_path, prompt);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	child_processend(t_cmd *current_node , int	filein, int fileout, t_prompt prompt)
{
	current_node->pid = fork();
	current_node->pid;
	if (current_node->pid == -1)
		error();
	if (current_node->pid == 0)
	{
		if (fileout != -1)
			dup2(fileout, 1);
		execute(current_node->full_cmd, current_node->full_path, prompt);
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
	int		i;
	int		status;
	int		j;

	j = 0;
	i = 0;
	filein = -1;
	fileout = -1;
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
			fileout = -1;
			i++;
		}
		i = 0;
		while (prompt.cmds->infile[i])
		{
			filein = open_file(prompt.cmds->infile[i], 2);
			if (prompt.cmds->infile[i++] == NULL)
				break;
			close(filein);
			filein = -1;
			i++;
		}
		dup2(filein, 0);
	}
	current_node = prompt.cmds;
	while (current_node->next != NULL)
	{
		if (j == 0)
			child_process1(current_node, filein, fileout, prompt);
		if (j != 0 && current_node->next != NULL)
			child_processmid(current_node, prompt);
		if (current_node->next == NULL)
			child_processend(current_node, filein, fileout, prompt);
		current_node = current_node->next;
	}
	current_node = prompt.cmds;
	while (current_node->next != NULL)
	{
		waitpid(current_node->pid, &status, NULL);
		current_node = current_node->next;
	}
	//check_status
	return (0);
}
