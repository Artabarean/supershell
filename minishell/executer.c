/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:07 by alex              #+#    #+#             */
/*   Updated: 2025/11/04 12:43:00 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	executer(t_prompt prompt)
{
	t_cmd	*cmd;
	int		last_status;
	int		status;

	cmd = prompt.cmds;
	if (prompt.cmds->infile[0] != NULL || prompt.cmds->outfile[0] != NULL)
		pipex(prompt);
	else
	{
		printf("Calling execute function\n");
		execute_(cmd, prompt);
		cmd = prompt.cmds;
		last_status = pid_stat(cmd ,prompt, status, last_status);
		check_status(last_status);
	}
}
