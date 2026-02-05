/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:39:38 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/05 15:40:53 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_all_processes(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt->pid[i])
	{
		kill(prompt->pid[i]);
		i++;
	}
}
