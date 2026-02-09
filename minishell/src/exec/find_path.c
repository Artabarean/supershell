/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:08:59 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/06 16:30:11 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printerr(t_prompt *pt, char *full_cmd, int j)
{
	char	*tmp;

	if (ft_strchr(full_cmd, '/'))
	{
		pt->error_msg[j] = ft_strdup("minishell: ");
		tmp = pt->error_msg[j];
		pt->error_msg[j] = ft_strjoin(tmp, full_cmd);
		free(tmp);
		tmp = pt->error_msg[j];
		if (full_cmd[0] == '.' && access(full_cmd, F_OK) == 0)
			pt->error_msg[j] = ft_strjoin(tmp, ": Permission denied\n");
		else
			pt->error_msg[j] = ft_strjoin(tmp, ": No such file or directory\n");
		free(tmp);
	}
	if (!ft_strchr(full_cmd, '/'))
	{
		pt->error_msg[j] = ft_strdup("minishell: ");
		tmp = pt->error_msg[j];
		pt->error_msg[j] = ft_strjoin(tmp, full_cmd);
		free(tmp);
		tmp = pt->error_msg[j];
		pt->error_msg[j] = ft_strjoin(tmp, ": command not found\n");
		free(tmp);
	}
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

	i = 0;
	if (cmd_isdir(cmd, cmd->full_cmd[0]))
		return (printerr(prompt, cmd->full_cmd[0], j), 1);
	if (!ft_strcmp(cmd->full_cmd[0], cmd->full_path))
		return (0);
	paths = ft_split(get_environments("PATH", prompt), ':');
	while (paths && paths[i])
	{
		cmd->full_path = joiner(paths[i], cmd);
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
	if (ispath(prompt) == 0)
		printerr(prompt, cmd->full_cmd[0], j);
	return (freer(paths), 1);
}

int	find_path_no_print(t_cmd *cmd, t_prompt *prompt)
{
	char	**paths;
	int		i;

	i = 0;
	if (cmd_isdir(cmd, cmd->full_cmd[0]))
	{
		if (access(cmd->full_cmd[0], F_OK) == -1)
		    prompt->exit_status = 127;
		else if (access(cmd->full_cmd[0], X_OK) == -1)
    		prompt->exit_status = 126;
		return (1);
	}
	if (!ft_strcmp(cmd->full_cmd[0], cmd->full_path))
		return (0);
	paths = ft_split(get_environments("PATH", prompt), ':');
	while (paths && paths[i])
	{
		cmd->full_path = joiner(paths[i], cmd);
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
	prompt->exit_status = 127;
	return (freer(paths), 1);
}
