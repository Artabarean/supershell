/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:39:14 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/12 17:02:16 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	unset_env(t_prompt *prompt, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = prompt->enviroment;
	prev = NULL;
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
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	builtin_unset(char **args, t_prompt *prompt)
{
	int	i;
	int	status;

	i = 1;
	printf("entering unset\n");
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
