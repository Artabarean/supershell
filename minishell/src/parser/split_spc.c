/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:28:14 by medel-ca          #+#    #+#             */
/*   Updated: 2026/02/07 17:40:39 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_spc(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	count_words(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_spc(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_spc(s[i]))
			i++;
	}
	return (count);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split_spc(const char *s)
{
	char	**res;
	int		i;
	int		j;
	int		start;

	if (!s || !*s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_spc(s[i]))
			i++;
		start = i;
		while (s[i] && !is_spc(s[i]))
			i++;
		if (start < i)
			res[j++] = word_dup(s, start, i);
	}
	res[j] = NULL;
	return (res);
}
