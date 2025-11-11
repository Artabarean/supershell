/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:54 by alex              #+#    #+#             */
/*   Updated: 2025/11/11 12:12:34 by atabarea         ###   ########.fr       */
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

void	child_process1(t_cmd *cmd , int fin, int fout, t_prompt *prompt, int i)
{
	int	n_cmds;

	find_path(cmd ,prompt);
	n_cmds = pipecount(*prompt) + 1;
	if (fin != -1)
	{
		dup2(fin, 0);
		close(fin);
	}
	dup2(fout, 1);
	close(fout);
	if (check_builtins(*prompt) == 1)
		exit(0);
	execute(cmd->full_cmd, cmd->full_path, *prompt);
}

void	child_processmid(t_cmd *cmd , t_prompt *prompt, int i)
{
	find_path(cmd ,prompt);
	dup2(prompt->pfd[i-1][0], 0);
	dup2(prompt->pfd[i][0], 1);
	close(prompt->pfd[i-1][0]);
	close(prompt->pfd[i][0]);
	if (check_builtins(*prompt) == 1)
		exit(0);
	execute(cmd->full_cmd, cmd->full_path, *prompt);
}

void	child_processend(t_cmd *cmd, int fout, t_prompt *prompt, int i)
{
	int	n_cmds;

	n_cmds = pipecount(*prompt) + 1;
	find_path(cmd ,prompt);
	dup2(prompt->pfd[i-1][0], 0);
	if (fout != -1)
	{
		dup2(fout, 1);
		close(fout);
	}
	closepfds(n_cmds, *prompt);
	if (check_builtins(*prompt) == 1)
		exit(0);
	execute(cmd->full_cmd, cmd->full_path, *prompt);
}

void	pipex(t_prompt prompt)
{
	int		filein;
	int		fileout;
	t_cmd	*current_node;
	int		last_status;
	int		status;

	filein = -1;
	fileout = -1;
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
}
