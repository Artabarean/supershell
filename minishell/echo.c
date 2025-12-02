/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:44:43 by codespace         #+#    #+#             */
/*   Updated: 2025/12/02 16:04:56 by medel-ca         ###   ########.fr       */
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
		}
		(printf("%s", full_cmd[i]));
		i++;	
		if (full_cmd[i] && full_cmd[i - 1][0] != '$')
			printf(" ");
	}
	if (ft_strncmp(full_cmd[1], "-n", 2) != 0)
		printf("\n");
}
