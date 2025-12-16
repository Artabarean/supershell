/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:48:13 by medel-ca          #+#    #+#             */
/*   Updated: 2025/12/16 16:50:03 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*extract_single_quote(char **input)
{
	int		len;
	char	*temp;

	len = 0;
	if (!input || !*input || **input != '\'')
		return (NULL);
	(*input)++;
	while ((*input)[len] && (*input)[len] != '\'')
		len++;
	if (!(*input)[len])
		return (NULL);
	temp = ft_substr(*input, 0, len);
	if (!temp)
		return (NULL);
	(*input) += len + 1;
	return (temp);
}

char	*extract_double_quote(char **input, t_env *env)
{
	int		len;
	char	*result;
	char	*part;

	len = 0;
	if (**input != '"')
		return (NULL);
	(*input)++;
	result = handle_quote_content(input, env);
	return (result);
}

char	*extract_and_expand(char **input, t_env *env)
{
	char	*buffer;

	if (!input || !*input)
		return (NULL);
	if (**input == '$')
		return (expand_or_empty(input, env));
	if (**input == '"')
		(*input)++;
	buffer = handle_quote_content(input, env);
	if (**input == '"')
		(*input)++;
	return (buffer);
}

char	*extract_word(char **input)
{
	int		len;
	char	*start;
	char	*word;

	if (!input || !*input)
		return (NULL);
	start = *input;
	len = 0;
	while ((**input && **input != ' ')
		|| **input == '|' || **input == '<' || **input == '>')
	{
		len++;
		(*input)++;
	}
	word = ft_substr(start, 0, len);
	if (!word)
		return (NULL);
	while (**input == ' ')
		(*input)++;
	return (word);
}
