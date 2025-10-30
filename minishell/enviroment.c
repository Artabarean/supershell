/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:06:53 by medel-ca          #+#    #+#             */
/*   Updated: 2025/10/30 20:06:53 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_env(t_env *e, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			e->path = ft_strdup(env[i] + 5);
		else if (!ft_strncmp(env[i], "HOME=", 5))
			e->home = ft_strdup(env[i] + 5);
		else if (!ft_strncmp(env[i], "PWD=", 4))
			e->pwd = ft_strdup(env[i] + 4);
		else if (!ft_strncmp(env[i], "OLDPWD=", 7))
			e->oldpwd = ft_strdup(env[i] + 7);
		else if (!ft_strncmp(env[i], "USER=", 5))
			e->user = ft_strdup(env[i] + 5);
		else if (!ft_strncmp(env[i], "SHELL=", 6))
			e->shell = ft_strdup(env[i] + 6);
		else if (!ft_strncmp(env[i], "SHLVL=", 6))
			e->shlvl = ft_atoi(env[i] + 6);
		else if (!ft_strncmp(env[i], "_=", 2))
			e->cmdpath = ft_strdup(env[i] + 2);
		i++;
	}
}
