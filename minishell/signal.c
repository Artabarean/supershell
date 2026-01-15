/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:00:09 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/12 16:57:49 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	close_child(int signal)
{
	g_exit_status = 130;
	printf("\n");
	(void)signal;
}

void	core_dump(int signal)
{
	g_exit_status = 131;
	printf("Quit (core dumped)\n");
	(void)signal;
}

void	close_heredoc(int signal)
{
	(void)signal;
	g_exit_status = 130;
	printf("warning: here-document at line "
		"1 delimited by end-of-file (wanted `EOF')\n");
	exit(g_exit_status);
}

void	reset_shell(int signal)
{
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
}

void	set_signal(int context, t_prompt *prompt)
{
	if (context == PROMPT_RESTART)
	{
		signal(SIGINT, reset_shell); // ctrl+C -> reinicia shell
		signal(SIGQUIT, SIG_IGN); // ctrl+\ -> se ignora
	}
	if (context == EXIT) // EOF (ctrl+D) -> se cierra la terminal si la línea está vacía
	{					// si hay texto se ignora
		printf("Exit\n");
		free_all(prompt);
		exit(EXIT_FAILURE);
	}
	if (context == CHILD_EXIT)
	{
		signal(SIGINT, close_child); // ctrl+C -> cierra proceso hijo
		signal(SIGQUIT, core_dump); // ctrl+\ -> cierra con core dumped
	}
	if (context == HEREDOC)
	{
		signal(SIGINT, close_heredoc); // ctrl+D al leer de heredoc
	}
}
