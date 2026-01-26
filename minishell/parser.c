/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:54 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/12 16:51:14 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_word(t_prompt *prompt, t_cmd *curr, int *i)
{
	add_arg_to_cmd(prompt->tkns[*i], curr);
	(*i)++;
}

static bool	handle_redirection(t_prompt *prompt, t_cmd *curr, int *i)
{
	if (!prompt->tkns[*i + 1] || prompt->types[*i + 1] != T_WORD)
		return (syntax_error(prompt->tkns[*i]), false);
	if (!create_file(prompt->types[*i], prompt->tkns[*i + 1], curr))
		return (syntax_error(prompt->tkns[*i]), false);
	*i += 2;
	return (true);
}

static bool	handle_pipe(t_prompt *prompt, t_cmd **curr)
{
	if (!(*curr)->full_cmd || !(*curr)->full_cmd[0])
		return (syntax_error("|"), false);
	(*curr)->next = create_cmd(prompt);
	*curr = (*curr)->next;
	return (true);
}

bool	parser(t_prompt *prompt, t_cmd *curr)
{
	int	i;

	i = 0;
	while (prompt->tkns[i])
	{
		if (!prompt->tkns[i])
			return (false);
		if (prompt->types[i] == T_PIPE)
		{
			if (!handle_pipe(prompt, &curr))
				return (false);
			i++;
		}
		else if (is_redirection_type(prompt->types[i]))
		{
			if (!handle_redirection(prompt, curr, &i))
				return (false);
		}
		else
			handle_word(prompt, curr, &i);
	}
	if (!curr->full_cmd && !curr->redir)
		return (syntax_error("newline"), false);
	curr->next = NULL;
	return (true);
}

bool	init_parser(t_prompt *prompt)
{
	t_cmd	*curr;

	if (!prompt || !prompt->tkns)
		return (0);
	curr = create_cmd(prompt);
	if (!curr)
		return (0);
	if (!parser(prompt, curr))
		return (0);
	return (1);
}
