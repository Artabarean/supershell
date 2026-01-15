/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:24 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/12 16:35:43 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*new_cmd(int value)
{
	t_cmd	*c;

	c = ft_calloc(1, sizeof(t_cmd));
	if (!c)
		return (NULL);
	c->full_cmd = ft_calloc(value + 1, sizeof(char *));
	if (!c->full_cmd)
		return (free(c), NULL);
	c->redir = NULL;
	c->full_path = NULL;
	c->next = NULL;
	return (c);
}

void	init_tkns(t_prompt *prompt)
{
	prompt->tkns = ft_calloc(prompt->tkns_nbr + 1, sizeof (char *));
	if (!prompt->tkns)
	{
		free_all(prompt);
		exit (EXIT_FAILURE);
	}
	prompt->types = ft_calloc(prompt->tkns_nbr, sizeof (t_toktype));
	if (!prompt->types)
	{
		free_all(prompt);
		exit (EXIT_FAILURE);
	}
	prompt->quotes = ft_calloc(prompt->tkns_nbr, sizeof (t_quote));
	if (!prompt->quotes)
	{
		free_all(prompt);
		exit (EXIT_FAILURE);
	}
}

void	init_prompt(t_prompt *prompt, char **envp)
{
	prompt->cmds = NULL;
	prompt->input = NULL;
	prompt->tkns = NULL;
	prompt->tkns_nbr = 0;
	prompt->pid = 0;
	init_env(prompt, envp);
}

t_cmd	*create_cmd(t_prompt *prompt)
{
	t_cmd	*current;

	current = new_cmd(prompt->tkns_nbr);
	add_cmd_back(&prompt->cmds, current);
	return (current);
}

int	count_input(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i])
			break ;
		count++;
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if (str[i] == str[i + 1])
				i++;
			i++;
		}
		else
		{
			while (str[i] && !is_separator(str[i]))
				i++;
		}
	}
	return (count);
}
