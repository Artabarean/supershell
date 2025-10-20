/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numoffds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:12:47 by atabarea          #+#    #+#             */
/*   Updated: 2025/10/20 13:17:44 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

pid_t	numoffds(char *argv[])
{
	int	i;
	int	j;
	
	i = 0;
	j = 1;
	while (argv[j])
	{
		while(argv[j][i])
		{
			if (argv[j][i] == '>' && argv[j][i++] != '\0')
			i++;
			//a lot more to do
		}
	}
	
}
