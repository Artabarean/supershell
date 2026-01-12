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

int	g_exit_status = 0;

void	start_minishell(t_prompt *prompt)
{
	if (!lexer(prompt))
	{
		free_all(prompt);
		return ;
	}
	expand_tkn(prompt);
	if (!init_parser(prompt))
	{
		free_all(prompt);
		return ;
	}
//	debug(*prompt);
	executer(prompt);
	free_all(prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;

	if (argc != 1 || envp == NULL || *envp == NULL)
		return (perror("Environment error"), 1);
	(void)argc;
	(void)argv;
	while (1)
	{
		init_prompt(&prompt, envp);
		get_user_input(&prompt);
		if (prompt.input == NULL)
			set_signal(EXIT, &prompt);
		else if (prompt.input && not_only_spaces(prompt.input))
		{
			if (correct_input(prompt.input))
				start_minishell(&prompt);
			else
				free_all(&prompt);
		}
	}
	return (0);
}

