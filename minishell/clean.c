/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:06:27 by medel-ca          #+#    #+#             */
/*   Updated: 2025/10/30 20:06:27 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_doble_ptr(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i] && i < MAX_TOKENS)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	del(t_cmd *tmp)
{
	if (!tmp)
		return ;
	if (tmp->full_cmd)
	{
		free_doble_ptr(tmp->full_cmd);
		tmp->full_cmd = NULL;
	}
	if (tmp->infile)
	{
		free_doble_ptr(tmp->infile);
		tmp->infile = NULL;
	}
	if (tmp->outfile)
	{
		free_doble_ptr(tmp->outfile);
		tmp->outfile = NULL;
	}
	if (tmp->full_path)
	{
		free(tmp->full_path);
		tmp->full_path = NULL;
	}
}

void	free_lst(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*tmp;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current->next;
		del(current);
		free(current);
		current = tmp;
	}
	*lst = NULL;
}

void	free_env(t_env *e)
{
	if (e)
	{
		free(e->path);
		free(e->home);
		free(e->pwd);
		free(e->oldpwd);
		free(e->user);
		free(e->shell);
		free(e->cmdpath);
		free(e);
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
		prompt->tkns = NULL;
	}
	if (prompt->cmds)
	{
		free_lst(&prompt->cmds);
	}
	if (prompt->input)
	{
		free(prompt->input);
		prompt->input = NULL;
	}
}
