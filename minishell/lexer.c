/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:40 by medel-ca          #+#    #+#             */
/*   Updated: 2025/12/02 12:56:57 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*extract_str(char **input)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*input)[len] && (*input)[len] != '\'')
		len++;
	while ((*input)[len] && (*input)[len] != ' ' )
		len++;
	temp = ft_substr_quotes(*input, 0, len);
	if (!temp)
		return (NULL);
	(*input) += len;
	return (temp);
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

void	lexer(t_prompt *prompt)
{
	int		i;
	char	*ptr;

	if (!prompt->input)
		return ;
	ptr = prompt->input;
	i = 0;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if (*ptr == '\'')
			prompt->tkns[i] = extract_str(&ptr);
		else if (*ptr == '"' || *ptr == '$')
			prompt->tkns[i] = extract_and_expand(&ptr, prompt->enviroment);
		else if (*ptr == '|' || *ptr == '<' || *ptr == '>')
			extract_sym(&ptr, prompt, i);
		else
			prompt->tkns[i] = extract_word(&ptr);
		if (!prompt->tkns[i] || prompt->tkns[i][0] == '\0')
			break ;
		i++;
	}
	prompt->tkns[i] = NULL;
	return ;
}
