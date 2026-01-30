/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:40 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/30 09:39:55 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(char c)
{
	return (c == ' ' || c == '\t'
		|| c == '|' || c == '<' || c == '>');
}

static char	*extract_word_part(char **input)
{
	int		len;
	char	*part;

	len = 0;
	while ((*input)[len] && !is_separator((*input)[len])
			&& (*input)[len] != '\'' && (*input)[len] != '"')
		len++;
	part = ft_substr(*input, 0, len);
	*input += len;
	return (part);
}

static char	*extract_part(char **input, t_quote *quote)
{
	if (**input == '\'')
	{
		*quote = Q_SINGLE;
		return (extract_single_quote(input));
	}
	if (**input == '"')
	{
		if (*quote != Q_SINGLE)
			*quote = Q_DOUBLE;
		return (extract_double_quote(input));
	}
	return (extract_word_part(input));
}

static char	*extract_token(char **input, t_prompt *prompt, int i)
{
	char	*token;
	char	*part;

	prompt->quotes[i] = Q_NONE;
	prompt->types[i] = T_WORD;
	token = ft_strdup("");
	if (!token)
		return (NULL);
	while (**input && !is_separator(**input))
	{
		part = extract_part(input, &prompt->quotes[i]);
		if (!part)
			return (free(token), NULL);
		token = ft_strjoin_free(token, part);
	}
	return (token);
}

int	lexer(t_prompt *prompt)
{
	int		i;
	char	*ptr;

	if (!prompt->input)
		return (0);
	ptr = prompt->input;
	i = 0;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if (!*ptr)
			break ;
		if (*ptr == '|' || *ptr == '<' || *ptr == '>')
		{
			extract_sym(&ptr, prompt, i++);
			continue ;
		}
		prompt->tkns[i] = extract_token(&ptr, prompt, i);
		if (!prompt->tkns[i])
			return (0);
		i++;
	}
	prompt->tkns[i] = NULL;
	return (1);
}
