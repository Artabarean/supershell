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

	prompt->pip_exec = 0;
	cmd = prompt->cmds;
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
		if(!execute_(cmd, prompt))
		{
			g_exit_status = pid_stat(cmd, prompt, g_exit_status);
			check_status(g_exit_status);
		}
	}
}
