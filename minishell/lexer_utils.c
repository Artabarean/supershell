/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:36 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/12 09:06:16 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	extract_sym_tkn(char **ptr, t_prompt *prompt, int i, t_toktype val)
{
	if (val == T_HEREDOC || val == T_APPEND)
	{
		prompt->tkns[i] = ft_substr(*ptr, 0, 2);
		prompt->types[i] = val;
		prompt->quotes[i] = Q_NONE;
	}
	else
	{
		prompt->tkns[i] = ft_substr(*ptr, 0, 1);
		prompt->types[i] = val;
		prompt->quotes[i] = Q_NONE;
	}
}

void	extract_sym(char **ptr, t_prompt *prompt, int index)
{
	if (**ptr == '<' && *(*ptr + 1) == '<')
	{
		extract_sym_tkn(ptr, prompt, index, T_HEREDOC);
		(*ptr)++;
	}
	else if (**ptr == '>' && *(*ptr + 1) == '>')
	{
		extract_sym_tkn(ptr, prompt, index, T_APPEND);
		(*ptr)++;
	}
	else if (*(*ptr) == '>' && *(*ptr + 1) != '>')
		extract_sym_tkn(ptr, prompt, index, T_REDIR_OUT);
	else if (*(*ptr) == '<' && *(*ptr + 1) != '<')
		extract_sym_tkn(ptr, prompt, index, T_REDIR_IN);
	else
		extract_sym_tkn(ptr, prompt, index, T_PIPE);
	(*ptr)++;
}
