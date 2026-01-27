/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:48:13 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/27 15:07:42 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*extract_double_quote(char **input)
{
	int		len;
	char	*temp;

	len = 0;
	if (**input != '"')
		return (NULL);
	(*input)++;
	while ((*input)[len] && (*input)[len] != '"')
		len++;
	if (!(*input)[len])
		return (NULL);
	temp = ft_substr(*input, 0, len);
	if (!temp)
		return (NULL);
	(*input) += len + 1;
	return (temp);
}
