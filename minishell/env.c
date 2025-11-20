/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:23:29 by codespace         #+#    #+#             */
/*   Updated: 2025/11/20 11:49:43 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	env(t_prompt *prompt, char **args)
{
	t_env	*env;

	if (args[1])
	{
		write(2, "minishell: env: ", 17);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": No such file or directory\n", 29);
		return (127);
	}
	env = prompt->enviroment;
	while (env)
	{
		if (env->value != NULL)
		{
			write(1, env->keyword, ft_strlen(env->keyword));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
