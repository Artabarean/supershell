/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:35:04 by atabarea          #+#    #+#             */
/*   Updated: 2025/12/15 14:23:43 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_error(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt->error[i])
	{
		ft_putstr_fd(prompt->error[i], 2);
		ft_putstr_fd("\n", 2);
		free(prompt->error[i]);
		i++;
	}
}
