/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:24:03 by atabarea          #+#    #+#             */
/*   Updated: 2025/06/17 14:29:08 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*memrsv;

	i = 0;
	memrsv = malloc(ft_strlen(s1) + ft_strlen(s2) * sizeof(char) + 1);
	if (memrsv == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		memrsv[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		memrsv[i] = *s2;
		s2++;
		i++;
	}
	memrsv[i] = '\0';
	return (memrsv);
}
