/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:19:43 by codespace         #+#    #+#             */
/*   Updated: 2025/11/14 11:32:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *get_env_value(t_env *env, const char *name)
{
    while (env)
    {
        if (env->key && strcmp(env->key, name) == 0)
            return env->value;
        env = env->next;
    }
    return (NULL);
}

int cd(char **args, t_prompt *prompt)
{
    char *path;
    char oldpwd[4096];

    if (!getcwd(oldpwd, sizeof(oldpwd)))
        return (1);
    if (!args[1] || !args[1][0])
    {
        path = get_env_value(prompt->env, "HOME");
        if (!path)
        {
            write(2, "minishell: cd: HOME not set\n", 29);
            return (1);
        }
    }
    else if (strcmp(args[1], "-") == 0)
    {
        path = get_env_value(prompt->env, "OLDPWD");
        if (!path)
        {
            write(2, "minishell: cd: OLDPWD not set\n", 30);
            return (1);
        }
        write(1, path, strlen(path));
        write(1, "\n", 1);
    }
    else
        path = args[1];
    if (chdir(path) != 0)
    {
        cd_error(path);
        return (1);
    }
    update_pwd_vars(prompt, oldpwd);
    return (0);
}
