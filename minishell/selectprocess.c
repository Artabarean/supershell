/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:59:00 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/27 13:05:05 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	selectprocess(t_prompt *prompt, t_cmd *cmd, int i, int *fin, int *fout)
{
	int	n_cmds;

	n_cmds = pipecount(*prompt) + 1;
	prompt->pid[i] = fork();
	if (prompt->pid[i] == -1)
		error("fork");
	if (prompt->pid[i] == 0)
	{
		file_opener(cmd, fout, fin);
		check_command(cmd, prompt);
		if (i == 0 || cmd->infile[0] != NULL)
		{
			if (n_cmds > 1)
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
