/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:40 by medel-ca          #+#    #+#             */
/*   Updated: 2025/12/17 11:06:37 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	extract_sym(char **ptr, t_prompt *prompt, int index)
{
	if (*(*ptr + 1) == '<' || *(*ptr + 1) == '>')
	{
		prompt->tkns[index] = ft_substr(*ptr, 0, 2);
		(*ptr)++;
	}
	else
		prompt->tkns[index] = ft_substr(*ptr, 0, 1);
	(*ptr)++;
}

int	is_separator(char c)
{
	return (c == ' ' || c == '\t'
		|| c == '|' || c == '<' || c == '>');
}

char	*extract_word_part(char **input)
{
	int		len;
	char	*part;

	len = 0;
	while ((*input)[len]
		&& !is_separator((*input)[len])
		&& (*input)[len] != '\''
		&& (*input)[len] != '"'
		&& (*input)[len] != '$')
		len++;
	part = ft_substr(*input, 0, len);
	*input += len;
	return (part);
}

char	*extract_token(char **input, t_env *env)
{
	char	*token;
	char	*part;
	char	*tmp;

	token = ft_strdup("");
	if (!token)
		return (NULL);
	while (**input && !is_separator(**input))
	{
		if (**input == '\'')
			part = extract_single_quote(input);
		else if (**input == '"')
			part = extract_double_quote(input, env);
		else if (**input == '$')
			part = expand_or_empty(input, env);
		else
			part = extract_word_part(input);
		if (!part)
			return (free(token), NULL);
		tmp = token;
		token = ft_strjoin_free(tmp, part);
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
		prompt->tkns[i] = extract_token(&ptr, prompt->enviroment);
		if (!prompt->tkns[i])
			return (0);
		i++;
	}
	prompt->tkns[i] = NULL;
	return (1);
}
