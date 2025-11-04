/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:54 by alex              #+#    #+#             */
/*   Updated: 2025/11/04 12:04:37 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	here_doc(char *limiter)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		error("pipe");
	reader = fork();
	set_signal(HEREDOC, NULL); // ctrl+D = EOF ¿como cierro el fd? 
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

void	child_process1(t_cmd *curr_node , int fin, int fout, t_prompt prompt, int i)
{
	int	j;

	j = pipecount(prompt);
	if (j > 0)
	{
		if (fin != -1)
		{
			dup2(prompt.pfd[i][0], fin);
			close(prompt.pfd[i][0]);
		}
		if (fout != -1)
		{
			dup2(prompt.pfd[i][1], fout);
			close(prompt.pfd[i][1]);
		}
	}
	prompt.pid = fork();
	if (prompt.pid == -1)
		error("pid");
	if (prompt.pid == 0)
	{
		dup2(fout, 1);
		if (check_builtins(prompt) == 1)
			exit(0);
		execute(curr_node->full_cmd, curr_node->full_path, prompt);
	}
}

void	child_processmid(t_cmd *curr_node , t_prompt prompt, int i)
{
	prompt.pid = fork();
	if (prompt.pid == -1)
		error("pid");
	if (prompt.pid == 0)
	{
		dup2(prompt.pfd[i-1][0], 0);
		dup2(prompt.pfd[i][1], 1);
		close(prompt.pfd[i-1][0]);
		close(prompt.pfd[i][1]);
		if (check_builtins(prompt) == 1)
			exit(0);
		execute(curr_node->full_cmd, curr_node->full_path, prompt);
	}
	else
	{
		close(prompt.pfd[i-1][0]);
		close(prompt.pfd[i][1]);
	}
}

void	child_processend(t_cmd *curr_node , int	fin, int fout, t_prompt prompt, int i)
{
	prompt.pid = fork();
	if (prompt.pid == -1)
		error("pid");
	if (prompt.pid == 0)
	{
		if (fout != -1)
			dup2(fout, 1);
		if (check_builtins(prompt) == 1)
			exit(0);
		execute(curr_node->full_cmd, curr_node->full_path, prompt);
	}
	else
	{
		if (fout != -1)
			close(fout);
		if (fin != -1)
			dup2(prompt.pfd[i-1][0], 0);
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
	find_path(prompt);
	// if (prompt.cmds->heredoc == 1)
	// {
	//  	fileout = open_file(*prompt.cmds->outfile, 0);
	//  	here_doc(*prompt.cmds->outfile);
	// }
	if (prompt.cmds->append == 1)
		fileout = open_file(*prompt.cmds->outfile, 0);
	else
	{
		file_opener(prompt, &fileout, &filein);
		dup2(filein, 0);
	}
	current_node = prompt.cmds;
	childprocess_(current_node, filein, fileout, prompt);
	current_node = prompt.cmds;
	last_status = pid_stat(current_node ,prompt, status, last_status);
	check_status(last_status);
	return (0);
}
