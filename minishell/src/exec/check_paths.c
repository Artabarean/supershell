/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:28:34 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/04 12:42:44 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_paths(t_cmd *cmd, char **paths)
{
	if (!paths)
	{
		if (cmd->full_cmd[0] && access(cmd->full_cmd[0], F_OK | X_OK) == 0)
		{
			cmd->full_path = cmd->full_cmd[0];
			return (0);
		}
	}
	else
	{
		if (cmd->full_cmd[0] && access(cmd->full_cmd[0], F_OK | X_OK) == 0)
		{
			cmd->full_path = cmd->full_cmd[0];
			return (0);
		}
	}
	return (1);
}
