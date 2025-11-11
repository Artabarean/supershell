/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:59:00 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/11 12:36:35 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	selectprocess(t_prompt *prompt, t_cmd *cmd, int i, int fin, int fout)
{
	int	n_cmds;

	n_cmds = pipecount(*prompt) + 1;
	prompt->pid = fork();
	if (prompt->pid == -1)
		error("fork");
	if (prompt->pid == 0)
	{
		if (i == 0)
		{
			if (n_cmds > 1)
			{
				printf("Llamada a la función child_process1\n");
				child_process1(cmd, fin, prompt->pfd[0][1], prompt, i);
			}
			else
				child_process1(cmd, fin, fout, prompt, i);
		}
		else if (i > 0 && (i + 1) < n_cmds)
		{
			printf("Llamada a la función child_processmid\n");
			child_processmid(cmd, prompt, i);
		}
		else if (i > 0 && (i + 1) == n_cmds)
		{
			printf("Llamada a la función child_processend\n");
			child_processend(cmd, fout, prompt, i);
		}
		exit(0);
	}
}
