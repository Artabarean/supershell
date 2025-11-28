/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:39:14 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/28 19:20:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    erase_in_env(t_prompt *prompt, char *name)
{
    int i;

    i = 0;
    while (prompt->enviroment->envp[i])
    {
        if (!ft_strcmp(prompt->enviroment->envp[i], name))
        {
            prompt->enviroment->envp[i] = NULL;
        }
        i++;
    }
}

int is_valid_identifier(const char *s)
{
    int i = 0;

    if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
        return (0);
    while (s[i])
    {
        if (!ft_isalnum(s[i]) && s[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

void unset_env(t_prompt *prompt, char *name)
{
    t_env *tmp = prompt->enviroment;
    t_env *prev = NULL;

    erase_in_env(prompt, name);
    while (tmp)
    {
        if (!ft_strcmp(tmp->keyword, name))
        {
            if (prev)
                prev->next = tmp->next;
            else
                prompt->enviroment = tmp->next;
            free(tmp->keyword);
            free(tmp->value);
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

int builtin_unset(char **args, t_prompt *prompt)
{
    int i; 
    int status;
    t_env *copy;

    i = 1;
    status = 0;
    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            printf("minishell: unset: `%s`: not a valid identifier\n", args[i]);
            status = 1;
        }
        else
            unset_env(prompt, args[i]);
        i++;
    }
    copy = prompt->enviroment;
    while (copy)
    {
        printf("keyword: %s, value: %s\n",copy->keyword, copy->value);
        copy = copy->next;
    }
    return (status);
}
