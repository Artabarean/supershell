#include "parser.h"

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	char		*user;
	int			i = 0;
	pid_t child_pid;
    int stat_loc;

	if (argc != 1 || envp == NULL || *envp == NULL)
		return (perror("Error en el enviroment"), 1);
	(void)argc;
	(void)argv;
	
	while (1)
	{
		//signals?
		init_prompt(&prompt, envp);
		user = ft_strjoin(prompt.enviroment->user, "@minishell: ");
		prompt.imput = readline(user);
		if (prompt.imput == NULL)
		{
			write(1, "\n", 1);
			return (0);
		}
		add_history(prompt.imput); 
		lexer(&prompt);
		parser(&prompt);
 		while (prompt.cmds->full_cmd)
		{
 			child_pid = fork();
        	if (child_pid == 0) 
			{
				execvp(prompt.cmds->full_cmd[0], prompt.cmds->full_cmd);
            	printf("This won't be printed if execvp is successul\n");
        	} 
			else 
			{
				waitpid(child_pid, &stat_loc, WUNTRACED);
			}			
			prompt.cmds->full_cmd++;	
		}
		//free_all(prompt);
	}
	return (0);
}