/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:06:53 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/30 09:51:04 by medel-ca         ###   ########.fr       */
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

void	init_env(t_prompt *prompt, char **env)
{
	int		i;
	t_env	*head;
	t_env	*current;

	if (!prompt || !env)
		return ;
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

char	*get_user(t_prompt *prompt)
{
	char	*temp;
	t_env	*env;

	env = prompt->enviroment;
	temp = NULL;
	while (env && !temp)
	{
		if (ft_strnstr(env->keyword, "USER", 4))
			temp = ft_strdup(env->value);
		env = env->next;
	}
	if (!temp)
		temp = ft_strdup("guest");
	return (temp);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

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
