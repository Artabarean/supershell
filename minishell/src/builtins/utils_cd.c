/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:24:39 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/06 16:22:55 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_parent(t_cmd *curr_nde, int *wstatus, int *last_status)
{
	
	if (curr_nde->next == NULL)
	{
		if (WIFEXITED(*wstatus))
			*last_status = WEXITSTATUS(*wstatus);
		else if (WIFSIGNALED(*wstatus))
		{
			*last_status = 128 + WTERMSIG(*wstatus);
		}
	}
}

int	checkfather_builtin(t_cmd *cmd)
{
	if (cmd->full_cmd && cmd->full_cmd[0])
	{
		if (!ft_strcmp(cmd->full_cmd[0], "cd"))
			return (1);
		if (!ft_strcmp(cmd->full_cmd[0], "unset"))
			return (1);
		if (!ft_strcmp(cmd->full_cmd[0], "export"))
			return (1);
	}
	return (0);
}

int	do_path(t_env *env, char *path, char *selection)
{
	if (!ft_strcmp(selection, "HOME"))
	{
		path = get_env_value(env, "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			return (1);
		}
	}
	else if (!ft_strcmp(selection, "OLDPWD"))
	{
		path = get_env_value(env, "OLDPWD");
		if (!path)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 29);
			return (1);
		}
	}
	return (0);
}

int	too_many_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_putendl_fd ("minishell: cd: too many arguments", 2);
		return (1);
	}
	return (0);
}

char	*printpath(t_prompt *prompt)
{
	char	*path;

	path = get_env_value(prompt->enviroment, "OLDPWD");
	ft_putendl_fd(path, 1);
	return (path);
}
