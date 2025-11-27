/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:30 by alex              #+#    #+#             */
/*   Updated: 2025/11/27 12:33:30 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	pid_stat(t_cmd *curr_nde, t_prompt *prompt, int last_status)
{
	int	i;
	int	n_cmds;

	i = 0;
	if (prompt->cmds->heredoc == 0)
	{
		n_cmds = (pipecount(*prompt) + 1);
		while (i < n_cmds && curr_nde)
		{
			waitpid(prompt->pid[i], &prompt->exit_stat, 0);
			if (curr_nde->next == NULL)
				last_status = prompt->exit_stat;
			curr_nde = curr_nde->next;
			i++;
		}
	}
	else
	{
		waitpid(prompt->pid[i], &prompt->exit_stat, 0);
		last_status = prompt->exit_stat;
	}
	return (last_status);
}

void	childprocess_(t_cmd *cmd, t_prompt *prompt)
{
	int	i;
	int	n_cmds;
	int	fin;
	int	fout;

	fin = -1;
	fout = -1;
	i = 0;
	n_cmds = pipecount(*prompt) + 1;
	pfd_alloc(prompt, n_cmds);
	single_builtin(pipecount(*prompt) + 1, cmd, prompt, fin, fout);
	while (i < n_cmds - 1)
	{
		if (pipe(prompt->pfd[i]) == -1)
			error("Pipe failed");
		i++;
	}
	i = 0;
	while (i < n_cmds && cmd)
	{
		selectprocess(prompt, cmd, i, &fin, &fout);
		cmd = cmd->next;
		i++;
	}
	closepfds(n_cmds, prompt);
}

void	file_opener(t_cmd *cmd, int *fileout, int *filein)
{
	int		i;

	i = 0;
	if (cmd->outfile)
	{
		while (cmd->outfile[i])
		{
			find_outfile(cmd, i, fileout);
			i++;
		}
	}
	i = 0;
	if (cmd->infile)
	{
		while (cmd->infile[i])
		{
			find_infile(cmd, i, filein);
			i++;
		}
	}
}

void	check_status(int exit_stat)
{
	int	exit_code;
	int	signal_num;

	if ((exit_stat & 0x7F) == 0)
	{
		exit_code = (exit_stat >> 8) & 0xFF;
		printf("Exited with code %d\n", exit_code);
	}
	else
	{
		signal_num = exit_stat & 0x7F;
		exit_code = 128 + signal_num;
		printf("Killed by signal %d\n", signal_num);
	}
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error(argv);
	return (file);
}
