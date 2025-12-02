/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:44:43 by codespace         #+#    #+#             */
/*   Updated: 2025/12/02 13:07:00 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	echo(char **full_cmd)
{
	int	i;

	i = 1;
	while (full_cmd[i])
	{
		if (ft_strncmp(full_cmd[i], "-n", 2) == 0)
		{
			while (full_cmd[i] != NULL && ft_strncmp(full_cmd[i], "-n", 2) == 0)
				i++;
			if (full_cmd[i] == NULL)
				return ;
			else
				(printf("%s", full_cmd[i]));
		}
		else
		{
			printf("%s\n", full_cmd[i]);
			return ;
		}
		i++;
	}
}
