/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:17:03 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/06 17:27:36 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pid_util(int *wstatus, t_prompt *prompt, int *last_status, int i)
{
	int sig;

	sig = WTERMSIG(*wstatus);
	if (sig == SIGQUIT)
	{
		if (i == prompt->n_cmds - 1)
			write(2, "Quit (core dumped)\n", 19);
		*last_status = 128 + SIGQUIT;
	}
	else if (sig == SIGINT)
		*last_status = 128 + SIGINT;
}
