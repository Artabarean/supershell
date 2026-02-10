/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:16:47 by medel-ca          #+#    #+#             */
/*   Updated: 2026/02/10 17:36:19 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	iter_shlvl(t_env *env)
{
	t_env	*cpyenv;
	int		lvl;

	if (!env)
		return ;
	cpyenv = env;
	while (cpyenv)
	{
		if (!ft_strcmp(cpyenv->keyword, "SHLVL"))
		{
			lvl = ft_atoi(cpyenv->value) + 1;
			free(cpyenv->value);
			cpyenv->value = ft_itoa(lvl);
			return ;
		}
		cpyenv = cpyenv->next;
	}
}

char	*get_user(t_prompt *prompt)
{
	char	*temp;
	t_env	*env;

	env = prompt->enviroment;
	temp = NULL;
	while (env && !temp)
	{
		if (ft_strnstr("USER", env->keyword, 4))
			temp = ft_strdup(env->value);
		env = env->next;
	}
	if (!temp)
		temp = ft_strdup("guest");
	return (temp);
}
