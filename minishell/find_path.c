/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:08:59 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/21 10:29:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	freer(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
}

char	*get_environments(char *name, t_prompt *prompt)
{
	t_env	*curr_env;
	char	*path;

	path = NULL;
	curr_env = prompt->enviroment;
	while (curr_env)
	{
		if (!ft_strcmp(name, curr_env->keyword))
			path = curr_env->value;
		curr_env = curr_env->next;
	}
	return (path);
}

int	find_path(t_cmd *cmd, t_prompt *prompt)
{
	int		i;
	char	**paths;
	int		j;

	i = -1;
	paths = ft_split(get_environments("PATH", prompt), ':');
	if (!paths)
	{
		if (cmd->full_cmd[0])
		{
			if (access(cmd->full_cmd[0], F_OK | X_OK) == 0)
				return (0);
			return (0);
		}
	}
	while (paths[++i])
	{
		cmd->full_path = ft_strjoin(paths[i], "/");
		cmd->full_path = ft_strjoin(cmd->full_path, cmd->full_cmd[0]);
		if (access(cmd->full_path, F_OK | X_OK) == 0)
			return (freer(paths), 0);
	}
	return (printf("%s: command not found\n", cmd->full_cmd[0]), 1);
}
