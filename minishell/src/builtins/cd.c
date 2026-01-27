/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:19:43 by codespace         #+#    #+#             */
/*   Updated: 2026/01/27 15:06:02 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env_value(t_env *env, const char *key, const char *value)
{
	while (env)
	{
		if (strcmp(env->keyword, key) == 0)
		{
			free(env->value);
			env->value = strdup(value);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

void	update_pwd_vars(t_prompt *prompt, const char *oldpwd)
{
	char	newpwd[4096];

	if (!getcwd(newpwd, sizeof(newpwd)))
		return ;
	set_env_value(prompt->enviroment, "OLDPWD", oldpwd);
	set_env_value(prompt->enviroment, "PWD", newpwd);
}

void	cd_error(const char *path)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, strlen(path));
	write(2, ": ", 2);
	write(2, strerror(errno), strlen(strerror(errno)));
	write(2, "\n", 1);
}

char	*get_env_value(t_env *env, const char *name)
{
	while (env)
	{
		if (env->keyword && strcmp(env->keyword, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

//	cd solo recibe un argumento
int	cd(char **args, t_prompt *prompt)
{
	char	*path;
	char	oldpwd[4096];

	path = NULL;
	if (!getcwd(oldpwd, sizeof(oldpwd)))
	{
		g_exit_status = 1;
		return (1);
	}
	if (args[2])
	{
		ft_putendl_fd ("minishell: cd: too many arguments", 2);
		g_exit_status = 1;
		return (1);
	}
	if (!args[1] || !args[1][0])
	{
		if (do_path(prompt->enviroment, path, "HOME") == 1)
		{
			g_exit_status = 1;
			return (1);
		}
		path = get_env_value(prompt->enviroment, "HOME");
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (do_path(prompt->enviroment, path, "OLDPWD") == 1)
		{
			g_exit_status = 1;
			return (1);
		}
		path = get_env_value(prompt->enviroment, "OLDPWD");
		ft_putendl_fd(path, 1);
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		g_exit_status = 1;
		return (cd_error(path), 1);
	}
	update_pwd_vars(prompt, oldpwd);
	return (0);
}
