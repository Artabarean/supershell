/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:24:39 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/12 17:04:44 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
