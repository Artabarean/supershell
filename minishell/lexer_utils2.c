/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:48:13 by medel-ca          #+#    #+#             */
/*   Updated: 2025/12/02 16:18:44 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*stract_str(char const *s, unsigned int start, size_t len, size_t quote)
{
	size_t	z;
	char	*subs;

	z = 0;
	subs = ft_calloc (len + 1 - quote, sizeof(char));
	if (subs == NULL)
		return (NULL);
	while (z < len && s[start + z])
	{
		if (s[start + z] != '\'' && s[start + z] != '"')
		{
			subs[z] = s[start + z];
			z++;
		}
		else
			start++;
	}
	return (subs);
}

char	*ft_substr_quotes(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	quote;

	quote = 0;
	if (!(s))
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup (""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (strchr(s, '\'') || strchr(s, '"'))
		quote = 1;
	subs = stract_str(s, start, len, quote);
	return (subs);
}
