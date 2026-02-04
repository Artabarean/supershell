/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_isdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:06:21 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/04 12:21:57 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*joiner(char *paths, t_cmd *cmd)
{
	char	*temp;

	temp = ft_strjoin(paths, "/");
	if (temp)
		cmd->full_path = ft_strjoin(temp, cmd->full_cmd[0]);
	if (temp)
		free(temp);
	if (cmd->full_path)
		return (cmd->full_path);
	return (NULL);
}

int	cmd_isdir(t_cmd *cmd, char *full_cmd)
{
	if (full_cmd)
	{
		if (ft_strchr(full_cmd, '/'))
		{
			if (full_cmd[0] == '.')
			{
				if (access(full_cmd, F_OK | X_OK) == 0)
					return (cmd->full_path = full_cmd, 0);
				if (access(full_cmd, F_OK) == 0 && access(full_cmd, X_OK) == 1)
					return (1);
			}
			if (access(full_cmd, F_OK | X_OK) == 0)
				return (0);
			else
				return (1);
		}
	}
	return (0);
}
