/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:08:59 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/03 17:43:59 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printerr(t_prompt *prompt, char *full_cmd, int j)
{
	char	*tmp;
	char	*msg;

	msg = ft_strdup("minishell: ");
	tmp = msg;
	msg = ft_strjoin(tmp, full_cmd);
	free(tmp);
	tmp = msg;
	msg = ft_strjoin(tmp, ": command not found\n");
	free(tmp);
	prompt->error_msg[j] = msg;
}

void	freer(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		free(paths[i]);
		i++;
	}
	if (paths)
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

int	find_path(t_cmd *cmd, t_prompt *prompt, int j)
{
	int		i;
	char	**paths;
	char	*temp;

	i = 0;
	paths = ft_split(get_environments("PATH", prompt), ':');
	while (paths && paths[i])
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
	if (check_paths(cmd, paths) == 0)
		return (freer(paths), 0);
	freer(paths);
	return (printerr(prompt, cmd->full_cmd[0], j), 1);
}

int	find_path_no_print(t_cmd *cmd, t_prompt *prompt)
{
	int		i;
	char	**paths;
	char	*temp;

	i = 0;
	paths = ft_split(get_environments("PATH", prompt), ':');
	while (paths && paths[i])
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
	if (check_paths(cmd, paths) == 0)
		return (freer(paths), 0);
	freer(paths);
	return (1);
}
