/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:39:14 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/10 17:21:05 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_last_node(t_env *node)
{
	free(node->keyword);
	free(node->value);
	free(node);
}

static void	set_previous_node(t_env *node, t_env *prev)
{
	free_last_node(node);
	prev->next = NULL;
}

static void	shift_env_data(t_env *curr)
{
	t_env	*next;

	while (curr->next)
	{
		next = curr->next;
		free(curr->keyword);
		free(curr->value);
		curr->keyword = ft_strdup(next->keyword);
		if (next->value)
			curr->value = ft_strdup(next->value);
		else
			curr->value = NULL;
		if (!next->next)
		{
			curr->next = NULL;
			free_last_node(next);
			break ;
		}
		curr = curr->next;
	}
}

static void	unset_env(t_prompt *prompt, char *name)
{
	t_env	*curr;
	t_env	*prev;

	if (!prompt || !prompt->enviroment)
		return ;
	curr = prompt->enviroment;
	prev = curr;
	while (curr)
	{
		if (curr->keyword)
		{
			if (!ft_strcmp(curr->keyword, name))
			{
				if (!curr->next)
				{
					set_previous_node(curr, prev);
					return ;
				}
				shift_env_data(curr);
				return ;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}

int	builtin_unset(char **args, t_prompt *prompt)
{
	int	i;
	int	status;

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
	return (status);
}
