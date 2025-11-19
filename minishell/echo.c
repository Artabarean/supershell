/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:44:43 by codespace         #+#    #+#             */
/*   Updated: 2025/11/19 11:59:44 by atabarea         ###   ########.fr       */
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
				return (printf("%s", full_cmd[i]), 0);
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
