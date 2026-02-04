/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:00:09 by medel-ca          #+#    #+#             */
/*   Updated: 2026/02/04 17:23:11 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_heredoc(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_done = 1;
	g_exit_status = 130;
}

static void	reset_shell(int signal)
{
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
}

void	set_signal(int context)
{
	if (context == SIG_PROMPT)
	{
		signal(SIGINT, reset_shell);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (context == SIG_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (context == SIG_WAIT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (context == SIG_HEREDOC)
	{
		//signal(SIGINT, close_heredoc);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}
