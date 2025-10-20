/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numofoutfds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:12:47 by atabarea          #+#    #+#             */
/*   Updated: 2025/10/20 14:27:11 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	numofoutfds(char *argv[])
{
	int	i;
	int	j;
	int	count;
	
	i = 0;
	count = 0;
	j = 1;
	while (argv[j])
	{
		while(argv[j][i])
		{
			if (argv[j][i] == '>' && (argv[j][i++] != '\0' || argv[j][i++] != '>'))
				count++;
			i++;
		}
		j++;
	}
	return (count);
}

int	numofinfds(char *argv[])
{
	int	i;
	int	j;
	int	count;
	
	i = 0;
	count = 0;
	j = 1;
	while (argv[j])
	{
		while(argv[j][i])
		{
			if (argv[j][i] == '<' && (argv[j][i++] != '\0' || argv[j][i++] != '<'))
				count++;
			i++;
		}
		j++;
	}
	return (count);	
}
