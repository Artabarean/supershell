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

#include "minishell.h"

volatile sig_atomic_t	g_sign = 0;

void	start_minishell(t_prompt *prompt)
{
	if (g_sign)
	{
		prompt->exit_status = g_sign;
		g_sign = 0;
	}
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

void	clean_exit(t_prompt *prompt)
{
	printf("exit\n");
	free_all(prompt);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;

	if (argc != 1 || envp == NULL || *envp == NULL)
		return (ft_putendl_fd("Environment error", 2), 1);
	(void)argv;
	init_prompt(&prompt, envp);
	while (1)
	{
		get_user_input(&prompt);
		if (prompt.input == NULL)
			clean_exit(&prompt);
		else if (prompt.input && not_only_spaces(prompt.input))
		{
			if (correct_input(prompt.input))
				start_minishell(&prompt);
			else
			{
				prompt.exit_status = 2;
				free_input(&prompt);
			}
		}
	}
	return (0);
}

