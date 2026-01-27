/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:39:14 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/27 15:17:43 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	erase_in_env(t_prompt *prompt, char *name)
// {
// 	int	i;

// 	i = 0;
// 	while (prompt->enviroment->envp[i])
// 	{
// 		if (!ft_strcmp(prompt->enviroment->envp[i], name))
// 		{
// 			prompt->enviroment->envp[i] = NULL;
// 		}
// 		i++;
// 	}
// }

static void	free_last_node(t_env *node)
{
	free(node->keyword);
	free(node->value);
	free(node);
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

void	unset_env(t_prompt *prompt, char *name)
{
	t_env	*curr;

	if (!prompt || !prompt->enviroment)
		return ;
	curr = prompt->enviroment;
	while (curr)
	{
		if (!ft_strcmp(curr->keyword, name))
		{
			if (!curr->next)
			{
				prompt->enviroment = NULL;
				free_last_node(curr);
				return ;
			}
			shift_env_data(curr);
			return ;
		}
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
