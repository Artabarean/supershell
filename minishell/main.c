/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:45 by medel-ca          #+#    #+#             */
/*   Updated: 2025/10/30 19:59:45 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

volatile sig_atomic_t	g_exit_status = 0;

void	start_minishell(t_prompt *prompt)
{
	if (!lexer(prompt))
	{
		free_input(prompt);
		return ;
	}
	expand_tkn(prompt);
	if (!init_parser(prompt))
	{
		free_input(prompt);
		return ;
	}
	//debug(*prompt);
	executer(prompt);
	free_input(prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;

	if (argc != 1 || envp == NULL || *envp == NULL)
		return (perror("Environment error"), 1);
	(void)argc;
	(void)argv;
	init_prompt(&prompt, envp);
	while (1)
	{
		get_user_input(&prompt);
		if (prompt.input == NULL)
			set_signal(EXIT, &prompt);
		else if (prompt.input && not_only_spaces(prompt.input))
		{
			if (correct_input(prompt.input))
				start_minishell(&prompt);
			else
				free_input(&prompt);
		}
	}
	return (0);
}





