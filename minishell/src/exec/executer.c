/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:07 by alex              #+#    #+#             */
/*   Updated: 2026/02/06 12:56:16 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executer(t_prompt *prompt)
{
	t_cmd	*cmd;

	prompt->pip_exec = 0;
	cmd = prompt->cmds;
	set_signal(SIG_PROMPT);
	while (cmd)
	{
		if (prompt->pip_exec == 0 && cmd->redir != NULL)
		{
			pipex(prompt);
			prompt->pip_exec = 1;
		}
		cmd = cmd->next;
	}
	if (prompt->pip_exec == 0)
	{
		cmd = prompt->cmds;
		prompt->pid = ft_calloc(sizeof(pid_t), (pipecount(*prompt) + 1));
		if (!execute_(cmd, prompt))
			prompt->exit_status = pid_stat(cmd, prompt, prompt->exit_status);
		free(prompt->pid);
	}
}
