#include "parser.h"

void	start_minishell(t_prompt *prompt)
{
	lexer(prompt);
	init_parser(prompt);
	executer(*prompt);
	free_all(prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	int			i;

	i = 0;
	if (argc != 1 || envp == NULL || *envp == NULL)
		return (perror("Error en el enviroment"), 1);
	(void)argc;
	(void)argv;
	while (1)
	{
		init_prompt(&prompt, envp, 1);
		get_user_input(&prompt);
		if (prompt.input && not_only_spaces(prompt.input))
		{
			if (correct_input(prompt.input))
				start_minishell(&prompt);
			else
				free_all(&prompt);
		}
		else
			set_signal(EXIT, &prompt);
	}
	return (0);
}
