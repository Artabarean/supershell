/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:23:29 by codespace         #+#    #+#             */
/*   Updated: 2025/11/14 11:28:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int env(t_prompt *prompt, char **args)
{
    t_env *env;

    if (args[1])
    {
        write(2, "minishell: env: ", 17);
        write(2, args[1], ft_strlen(args[1]));
        write(2, ": No such file or directory\n", 29);
        return (127);
    }
    env = prompt->env;
    while (env)
    {
        if (env->value != NULL)
        {
            write(1, env->key, ft_strlen(env->key));
            write(1, "=", 1);
            write(1, env->value, ft_strlen(env->value));
            write(1, "\n", 1);
        }
        env = env->next;
    }
    return (0);
}
