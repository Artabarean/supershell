/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:23:47 by atabarea          #+#    #+#             */
/*   Updated: 2025/06/11 10:42:11 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strdup(const char *s)
{
	char	*clone;
	int		i;

	i = 0;
	clone = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (clone == NULL)
	{
		return (NULL);
	}
	while (*s != '\0')
	{
		clone[i] = *s;
		s++;
		i++;
	}
	clone[i] = '\0';
	return (clone);
}
