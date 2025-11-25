/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:07 by alex              #+#    #+#             */
/*   Updated: 2025/11/25 11:41:20 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
// int		checkcmd(t_cmd *cmd)
// {
// 	if (cmd->full_cmd)
// 		return (0);
// 	if (cmd->infile[0] != NULL)
// 	{	
// 		if (access(cmd->infile[0], O_RDONLY) != 0)
// 			printf("Minishell: %s: Permission denied\n", cmd->infile[0]);
// 	}
// 	if (cmd->outfile[0] != NULL)
// 	{
// 		if (access(cmd->outfile[0], O_WRONLY) != 0)
// 			printf("Minishell: %s: Permission denied\n", cmd->infile[0]);
// 	}
// 	return (1);
// }

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
				// if (checkcmd(cmd) == 0)
				pipex(*prompt);
				prompt->pip_exec = 1;
			}
		cmd = cmd->next;
	}
	if (prompt->pip_exec == 0)
	{
		cmd = prompt->cmds;
		prompt->pid = malloc(sizeof(pid_t) * (pipecount(*prompt) + 1));
		execute_(cmd, prompt);
		last_status = pid_stat(cmd ,prompt, last_status);
		check_status(last_status);
	}
}
