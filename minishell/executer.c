/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:07 by alex              #+#    #+#             */
/*   Updated: 2025/11/26 11:20:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	executer(t_prompt *prompt)
{
	t_cmd	*cmd;
	int		last_status;

	prompt->pip_exec = 0;
	cmd = prompt->cmds;
	while (cmd)
	{
		printf("pipex_exec: %d\n", prompt->pip_exec);
		if (prompt->pip_exec == 0)
			if (cmd->infile[0] != NULL || cmd->outfile[0] != NULL)
			{
				pipex(*prompt);
				prompt->pip_exec = 1;
			}
		cmd = cmd->next;
	}
	if (prompt->pip_exec == 0)
	{
		cmd = prompt->cmds;
		prompt->pid = malloc(sizeof(pid_t) * (pipecount(*prompt) + 1));
		printf("calling execute\n");
		execute_(cmd, prompt);
		last_status = pid_stat(cmd ,prompt, last_status);
		check_status(last_status);
	}
}
