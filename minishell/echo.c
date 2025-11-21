/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:44:43 by codespace         #+#    #+#             */
/*   Updated: 2025/11/21 10:53:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	echo(char **full_cmd)
{
	int	i;

	i = 1;
	while (full_cmd[i])
	{
		if (full_cmd[0][0] == '-')
			return ;
		if (ft_strncmp(full_cmd[i], "-n", 2) == 0)
		{
			i++;
			if (full_cmd[i][0] == '-' || full_cmd[i] == NULL)
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
