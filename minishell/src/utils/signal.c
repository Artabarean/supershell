/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:00:09 by medel-ca          #+#    #+#             */
/*   Updated: 2026/02/09 14:58:40 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_heredoc(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	g_sign = 130;
	exit(130);

}

static void	reset_shell(int signal)
{
	
	(void)signal;
	write(1, "\n", 1);	
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sign = 130;
}

void	set_signal(int context)
{
	struct sigaction sa;

   	sigemptyset(&sa.sa_mask);
	if (context == SIG_PROMPT)
	{
		sa.sa_handler = reset_shell;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
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
    	sa.sa_handler = close_heredoc;
		sa.sa_flags = 0;
    	sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}
