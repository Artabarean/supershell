/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:07 by alex              #+#    #+#             */
/*   Updated: 2025/10/31 11:54:33 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	executer(t_prompt prompt)
{
	t_cmd	*cmd;

	cmd = prompt.cmds;
	if (prompt.cmds->infile && prompt.cmds->outfile)
		pipex(prompt);
	else
	{
		while (cmd)
		{
			
			execute_(prompt.cmds->full_cmd, prompt.cmds->full_path, prompt);
			cmd = cmd->next;
		}
	}
}
