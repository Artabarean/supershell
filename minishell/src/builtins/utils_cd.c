/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:24:39 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/30 13:20:58 by atabarea         ###   ########.fr       */
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
			if (WTERMSIG(*wstatus) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			if (WTERMSIG(*wstatus) == SIGINT)
				write(1, "\n", 1);
		}
	}
}

int	checkfather_builtin(t_cmd *cmd)
{
	if (cmd->full_cmd[0])
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
