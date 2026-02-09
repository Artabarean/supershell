/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:49:17 by codespace         #+#    #+#             */
/*   Updated: 2026/02/09 16:41:16 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if ((!str || (!ft_isalpha(str[0]) && str[0] != '_')) && str[0] != '$')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static t_env	*env_find(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->keyword, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	env_add_or_update(t_prompt *prompt, char *arg)
{
	t_env	*node;
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		value = ft_strdup(eq + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	node = env_find(prompt->enviroment, key);
	if (node)
	{
		free(node->value);
		node->value = value;
		free(key);
	}
	else
		update_node(node, prompt, key, value);
}

static int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env && ++i)
		env = env->next;
	return (i);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	char	*temp;
	int		i;

	i = 0;
	arr = malloc(sizeof(char *) * (env_size(env) + 1));
	while (env)
	{
		if (env->value)
		{
			temp = ft_strjoin(env->keyword, "=");
			arr[i] = ft_strjoin(temp, env->value);
			free(temp);
		}
		else
			arr[i] = ft_strdup(env->keyword);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
