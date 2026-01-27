#include "minishell.h"


void	print_tokens(char **tokens)
{
	int i = 0;
	
	printf(GREEN"=== Tokens ===\n"RESET);
	while(tokens[i])
	{
		printf("Token n. %d: %s\n", i + 1, tokens[i]);
		i++;
	}
	printf(GREEN"---------------\n"RESET);
}

const char	*toktype_to_str(t_toktype type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_APPEND)
		return ("APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	print_cmds(t_cmd *cmds)
{
	int i;
	t_redir *redir;
	while (cmds)
	{
		printf(GREEN"=== Comando ===\n"RESET);
		printf("Args: ");
		if (cmds->full_cmd)
		{
			i = 0;
			while (cmds->full_cmd[i])
			{
				printf("\"%s\" ", cmds->full_cmd[i]);
				i++;
			}
		}
		printf("\n");
		printf("Redirections: \n");
		redir = cmds->redir;
		while (redir)
		{
			printf("\"%s\" ", redir->file);
			printf("\"%s\" ", toktype_to_str(redir->type));
			printf("\n");
			redir = redir->next;
		}
		printf("\n");
		printf(GREEN"---------------\n"RESET);
		cmds = cmds->next;
	}
}

void	print_env(t_env *enviroment)
{
	while (enviroment->next)
	{
		printf("Keyword: %s\n", enviroment->keyword);
		printf("Value: %s\n", enviroment->value);
		enviroment = enviroment->next;
	}
}

void	debug(t_prompt prompt)
{
	print_tokens(prompt.tkns);
	print_cmds(prompt.cmds);
//	print_env(prompt.enviroment);
}