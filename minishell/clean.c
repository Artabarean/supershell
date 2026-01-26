/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:06:27 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/26 13:06:24 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_doble_ptr(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir);
		redir = tmp;
	}
}

void	free_cmds(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*tmp;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current->next;
		if (current->full_cmd)
		{
			free_doble_ptr(current->full_cmd);
			current->full_cmd = NULL;
		}
		if (current->redir)
			free_redir(current->redir);
		free(current);
		current = tmp;
	}
	*lst = NULL;
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	//int		i;

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

void	free_all(t_prompt *prompt)
{
	if (!prompt)
		return ;
	if (prompt->enviroment)
	{
		free_env(prompt->enviroment);
		prompt->enviroment = NULL;
	}
	if (prompt->tkns)
	{
		free_doble_ptr(prompt->tkns);
		free(prompt->types);
		free(prompt->quotes);
		prompt->tkns = NULL;
		prompt->types = NULL;
		prompt->quotes = NULL;
	}
	if (prompt->cmds)
		free_cmds(&prompt->cmds);
	if (prompt->input)
	{
		free(prompt->input);
		prompt->input = NULL;
	}
}

void	free_input(t_prompt *prompt)
{
	if (!prompt)
		return ;
	if (prompt->tkns)
	{
		free_doble_ptr(prompt->tkns);
		free(prompt->types);
		free(prompt->quotes);
		prompt->tkns = NULL;
		prompt->types = NULL;
		prompt->quotes = NULL;
	}
	if (prompt->cmds)
	{
		free_cmds(&prompt->cmds);
	}
	if (prompt->input)
	{
		free(prompt->input);
		prompt->input = NULL;
	}
}
