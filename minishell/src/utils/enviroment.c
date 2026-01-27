/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:06:53 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/27 15:06:22 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	fill_env(char *env, t_env *e)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	e->keyword = ft_substr(env, 0, i);
	e->value = ft_substr(env, i + 1, (ft_strlen(env) - (i + 1)));
}

t_env	*new_env(void)
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
