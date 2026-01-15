/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:07 by alex              #+#    #+#             */
/*   Updated: 2026/01/12 16:22:22 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
//actualizada la función con la nueva estructura
void	executer(t_prompt *prompt)
{
	t_cmd	*cmd;
	int		last_status;

	prompt->exit_stat = 0;
	prompt->pip_exec = 0;
	cmd = prompt->cmds;
	last_status = 0;
	while (cmd)
	{
		if (prompt->pip_exec == 0 && cmd->redir != NULL)
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
//		printf("calling execute\n");
		execute_(cmd, prompt);
		last_status = pid_stat(cmd, prompt, last_status);
		check_status(last_status);
	}
}
