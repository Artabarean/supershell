/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:15:09 by atabarea          #+#    #+#             */
/*   Updated: 2025/06/11 16:24:19 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wrdcnt(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] == c)
		i++;
	if (s[i] == '\0' && c != '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != c && s[i + 1] == c)
			count++;
		if (s[i + 1] == '\0' && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_lttrcnt(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] == c)
		i++;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static char	*ft_createstr(char const *s, char c, size_t len)
{
	size_t	i;
	size_t	j;
	char	*aux;

	j = 0;
	i = 0;
	if (s[i] == c)
		i++;
	aux = malloc(sizeof(char) * (len + 1));
	if (!aux)
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
	{
		aux[j] = s[i];
		i++;
		j++;
	}
	aux[j] = '\0';
	return (aux);
}

static char	**ft_split2(char c, char **str, char *aux, size_t arrcnt)
{
	size_t	index;

	index = 0;
	while (*aux == c)
		aux++;
	while (arrcnt > 0)
	{
		str[index] = ft_createstr(aux, c, ft_lttrcnt((const char *)aux, c));
		if (!str[index])
		{
			while (index > 0)
				free(str[--index]);
			free(str);
			return (NULL);
		}
		while (*aux != c && *aux != '\0')
			aux++;
		while (*aux == c)
			aux++;
		index++;
		arrcnt--;
	}
	return (str[index] = NULL, str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	char	*aux;
	size_t	arrcnt;

	if (!s)
		return (NULL);
	arrcnt = ft_wrdcnt(s, c);
	aux = (char *)s;
	str = (char **)malloc((arrcnt + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (ft_split2(c, str, aux, arrcnt));
}
