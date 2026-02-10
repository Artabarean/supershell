/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:06:53 by medel-ca          #+#    #+#             */
/*   Updated: 2026/02/10 17:36:06 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_env(char *env, t_env *e)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	e->keyword = ft_substr(env, 0, i);
	e->value = ft_substr(env, i + 1, (ft_strlen(env) - (i + 1)));
}

static t_env	*new_env(void)
{
	t_env	*current;

	current = ft_calloc(1, sizeof(t_env));
	if (!current)
		return (NULL);
	current->keyword = NULL;
	current->value = NULL;
	current->next = NULL;
	return (current);
}

t_env	*empty_env(void)
{
	t_env	*head;
	t_env	*current;
	char	cwd[PATH_MAX];

	current = new_env();
	head = current;
	current->keyword = ft_strdup("PWD");
	if (!getcwd(cwd, PATH_MAX))
		current->value = ft_strdup("");
	else
		current->value = ft_strdup(cwd);
	current->next = new_env();
	current = current->next;
	current->keyword = ft_strdup("SHLVL");
	current->value = ft_strdup("1");
	current->next = new_env();
	current = current->next;
	current->keyword = ft_strdup("_");
	current->value = ft_strdup("/usr/bin/env");
	current->next = new_env();
	current = current->next;
	current->keyword = ft_strdup("PATH");
	current->value = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:\
/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
	return (head);
}

void	init_env(t_prompt *prompt, char **env)
{
	int		i;
	t_env	*head;
	t_env	*current;

	if (!prompt || !env || !*env)
	{
		prompt->enviroment = empty_env();
		return ;
	}
	head = new_env();
	if (!head)
		return ;
	prompt->enviroment = head;
	current = head;
	i = 0;
	while (env[i])
	{
		fill_env(env[i], current);
		if (env[i + 1])
		{
			current->next = new_env();
			current = current->next;
		}
		i++;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		if (env->keyword)
			free(env->keyword);
		if (env->value)
			free(env->value);
		env = tmp->next;
		free(tmp);
	}
}
