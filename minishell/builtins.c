/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:58:47 by atabarea          #+#    #+#             */
/*   Updated: 2025/10/31 13:09:38 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		return (1);
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

int	echo(char **full_cmd)
{
	int	i;

	i = 1;
	while (full_cmd[i])
	{
		if (full_cmd[0][0] == '-')
			return (1);
		if (ft_strncmp(full_cmd[i], "-n", 2) == 0)
		{
			i++;
			if (full_cmd[i][0] == '-' || full_cmd[i] == NULL)
				return (1);
			else
			{
				printf("%s", full_cmd[i]);
				return (0);
			}
		}
		else
		{
			printf("%s\n", full_cmd[i]);
			return (0);
		}
		i++;
	}
	return (1);
}
