/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:08:59 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/27 12:19:24 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	printerr(char *full_cmd)
{
	ft_putstr_fd("Minishell: ", 2); 
	ft_putstr_fd(full_cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	freer(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
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
	char	*temp;

	i = 0;
	paths = ft_split(get_environments("PATH", prompt), ':');
	if (!paths)
	{
		if (cmd->full_cmd[0] && access(cmd->full_cmd[0], F_OK | X_OK) == 0)
			return (0);
		return (1);
	}
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			i++;
		cmd->full_path = ft_strjoin(temp, cmd->full_cmd[0]);
		free(temp);
		if (!cmd->full_path)
			i++;
		if (access(cmd->full_path, F_OK | X_OK) == 0)
			return (freer(paths), 0);
		free(cmd->full_path);
		cmd->full_path = NULL;
		i++;
	}
	freer(paths);
	return (printerr(cmd->full_cmd[0]), 1);
}

int	find_path_no_print(t_cmd *cmd, t_prompt *prompt)
{
	int		i;
	char	**paths;
	char	*temp;

	i = 0;
	paths = ft_split(get_environments("PATH", prompt), ':');
	if (!paths)
	{
		if (cmd->full_cmd[0] && access(cmd->full_cmd[0], F_OK | X_OK) == 0)
			return (0);
		return (1);
	}
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			i++;
		cmd->full_path = ft_strjoin(temp, cmd->full_cmd[0]);
		free(temp);
		if (!cmd->full_path)
			i++;
		if (access(cmd->full_path, F_OK | X_OK) == 0)
			return (freer(paths), 0);
		free(cmd->full_path);
		cmd->full_path = NULL;
		i++;
	}
	freer(paths);
	return (1);
}
