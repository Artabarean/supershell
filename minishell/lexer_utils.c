/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:36 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/08 21:59:33 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	extract_tkn(char **ptr, t_prompt *prompt, int index, t_toktype value)
{
	if (value == T_HEREDOC || value == T_APPEND)
	{
		prompt->tkns[index] = ft_substr(*ptr, 0, 2);
		prompt->types[index] = value;
		prompt->quotes[index] = Q_NONE;
	}
	else
	{
		prompt->tkns[index] = ft_substr(*ptr, 0, 1);
		prompt->types[index] = value;
		prompt->quotes[index] = Q_NONE;
	}
}

void	extract_sym(char **ptr, t_prompt *prompt, int index)
{
	if (*(*ptr + 1) == '<')
	{
		extract_tkn(ptr, prompt, index, T_HEREDOC);
		(*ptr)++;
	}
	else if (*(*ptr + 1) == '>')
	{
		extract_tkn(ptr, prompt, index, T_APPEND);
		(*ptr)++;
	}
	else if (*(*ptr) == '>' && *(*ptr + 1) != '>')
		extract_tkn(ptr, prompt, index, T_REDIR_OUT);
	else if (*(*ptr) == '<' && *(*ptr + 1) != '<')
		extract_tkn(ptr, prompt, index, T_REDIR_IN);
	else
		extract_tkn(ptr, prompt, index, T_PIPE);
	(*ptr)++;
}
