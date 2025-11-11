/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:07 by alex              #+#    #+#             */
/*   Updated: 2025/11/11 13:02:25 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	executer(t_prompt prompt)
{
	t_cmd	*cmd;
	int		last_status;
	int		status;
	int		pipex_executed;

	pipex_executed = 0;
	cmd = prompt.cmds;
	while (cmd)
	{
		if (pipex_executed == 0)
			if (cmd->infile[0] != NULL || cmd->outfile[0] != NULL)
			{
				pipex(prompt);
				pipex_executed = 1;
			}
		cmd = cmd->next;
	}
	if (pipex_executed == 0)
	{
		cmd = prompt.cmds;
		printf("Calling execute function\n");
		execute_(cmd, prompt);
		last_status = pid_stat(cmd ,prompt, status, last_status);
		check_status(last_status);
	}
}
