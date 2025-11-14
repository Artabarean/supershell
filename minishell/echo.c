/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:44:43 by codespace         #+#    #+#             */
/*   Updated: 2025/11/14 10:46:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	echo(char **full_cmd)
{
	int	i;

	i = 1;
	while (full_cmd[i])
	{
		if (full_cmd[0][0] == '-')
			return (1);
		if (ft_strncmp(full_cmd[i], "-n", 2) == 0)
		{
			i++;
			if (full_cmd[i][0] == '-' || full_cmd[i] == NULL)
				return (1);
			else
			{
				printf("%s", full_cmd[i]);
				return (0);
			}
		}
		else
		{
			printf("%s\n", full_cmd[i]);
			return (0);
		}
		i++;
	}
	return (1);
}
