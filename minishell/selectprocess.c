/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:59:00 by atabarea          #+#    #+#             */
/*   Updated: 2025/12/01 10:30:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	selectprocess(t_prompt *prompt, t_cmd *cmd, int i, int *fin, int *fout)
{
	int	n_cmds;
	int last;
	int hd_fd;

	n_cmds = pipecount(*prompt) + 1;
	prompt->pid[i] = fork();
	if (prompt->pid[i] == -1)
		error("fork");
	if (prompt->pid[i] == 0)
	{
		file_opener(cmd, fout, fin);
		if (cmd->heredoc && cmd->heredoc[0])
		{
			last = count_strs(cmd->heredoc) - 1;
			hd_fd = open(cmd->heredoc[last], O_RDONLY);
			if (hd_fd == -1)
				error("heredoc open failed");
			dup2(hd_fd, STDIN_FILENO);
			close(hd_fd);
			*fin = STDIN_FILENO;
		}
		check_command(cmd, prompt);
		if (i == 0 || cmd->infile[0] != NULL)
		{
			if (n_cmds > 1 && i == 0)
				child_process1(cmd, *fin, prompt->pfd[0][1], prompt);
			else
				child_process1(cmd, *fin, *fout, prompt);
		}
		else if (i > 0 && (i + 1) < n_cmds)
			child_processmid(cmd, prompt, i);
		else if (i > 0 && (i + 1) == n_cmds)
			child_processend(cmd, *fout, prompt, i);
		exit(0);
	}
}
