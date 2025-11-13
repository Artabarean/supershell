/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:58:47 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/13 09:49:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	check_builtins(t_prompt prompt)
{
	t_cmd *cmd;

	cmd = prompt.cmds;
	if (ft_strncmp(cmd->full_cmd[0], "echo", 4) == 0)
	{
		if (echo(prompt.cmds->full_cmd) == 1)
			return (error("echo"), 1);
		return (1);
	}
	if (ft_strncmp(cmd->full_cmd[0], "export", 6) == 0)
	{
		if (export(prompt.cmds->full_cmd) == 1)
			return (error("export"), 1);
		return (1);
	}
	if (ft_strncmp(cmd->full_cmd[0], "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->full_cmd[0], "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->full_cmd[0], "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->full_cmd[0], "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd->full_cmd[0], "unset", 5) == 0)
		return (1);
	return (0);
}

