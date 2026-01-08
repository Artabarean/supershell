/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:24 by medel-ca          #+#    #+#             */
/*   Updated: 2025/12/05 10:01:35 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*c;

	c = ft_calloc(1, sizeof(t_cmd));
	if (!c)
		return (NULL);
	c->full_cmd = ft_calloc(MAX_TOKENS, sizeof(char *));
	if (!c->full_cmd)
		return (free(c), NULL);
	c->infile = ft_calloc(MAX_TOKENS, sizeof(char *));
	if (!c->infile)
		return (free(c->full_cmd), free(c), NULL);
	c->outfile = ft_calloc(MAX_TOKENS, sizeof(char *));
	if (!c->outfile)
		return (free(c->infile), free(c->full_cmd), free(c), NULL);
	c->heredoc = ft_calloc(MAX_TOKENS, sizeof(char *));
	if (!c->heredoc)
		return (free(c->infile), free(c->outfile), free(c->full_cmd), free(c), NULL);
	c->app_doc = ft_calloc(MAX_TOKENS, sizeof(char *));
	if (!c->app_doc)
		return (free(c->heredoc), free(c->infile), free(c->outfile), free(c->full_cmd), free(c), NULL);
	c->full_path = NULL;
	c->append = 0;
	c->next = NULL;
	return (c);
}

void	init_tkns(t_prompt *prompt)
{
	prompt->tkns = ft_calloc(sizeof (char *), MAX_TOKENS);
	if (!prompt->tkns)
	{
		free_all(prompt);
		exit (EXIT_FAILURE);
	}
	prompt->types = ft_calloc(sizeof (t_toktype), MAX_TOKENS);
	if (!prompt->types)
	{
		free_all(prompt);
		exit (EXIT_FAILURE);
	}
	prompt->quotes = ft_calloc(sizeof (t_quote), MAX_TOKENS);
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
	prompt->pid = 0;
	init_env(prompt, envp);
	init_tkns(prompt);
}

t_cmd	*create_cmd(t_prompt *prompt)
{
	t_cmd	*current;

	current = new_cmd();
	add_cmd_back(&prompt->cmds, current);
	return (current);
}
