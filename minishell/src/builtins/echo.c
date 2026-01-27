/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:44:43 by codespace         #+#    #+#             */
/*   Updated: 2026/01/27 15:06:17 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **full_cmd, t_env *env)
{
	int		i;
	int		no_newline;
	char	*arg;

	no_newline = 0;
	i = 1;
	(void)env;
	while (full_cmd[i] && ft_strncmp(full_cmd[i], "-n", 2) == 0)
	{
		no_newline = 1;
		i++;
	}
	while (full_cmd[i])
	{
		arg = full_cmd[i];
		printf("%s", arg);
		if (full_cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
}
