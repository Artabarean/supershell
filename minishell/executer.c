/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:07 by alex              #+#    #+#             */
/*   Updated: 2025/12/02 10:52:16 by atabarea         ###   ########.fr       */
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
		if (prompt->pip_exec == 0)
			if (cmd->infile[0] != NULL || cmd->outfile[0] != NULL 
				|| cmd->heredoc[0] != NULL)
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
