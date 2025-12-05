#include "parser.h"


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

void	print_cmds(t_cmd *cmds)
{
	int i;
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
		printf("Infiles: ");
		if (cmds->infile)
		{
			i = 0;
			while (cmds->infile[i])
			{
				printf("\"%s\" ", cmds->infile[i]);
				i++;
			}
		}
		printf("\n");
		printf("Heredoc: ");
		if (cmds->heredoc)
		{
			i = 0;
			while (cmds->heredoc[i])
			{
				printf("\"%s\" ", cmds->heredoc[i]);
				i++;
			}
		}
		printf("\n");
		printf("Outfiles: ");
		if (cmds->outfile)
		{
			i = 0;
			while (cmds->outfile[i])
			{
				printf("\"%s\" ", cmds->outfile[i]);
				i++;
			}
		}
		printf("\n");
		printf("Append: ");
		if (cmds->tmp_doc)
		{
			i = 0;
			while (cmds->tmp_doc[i])
			{
				printf("\"%s\" ", cmds->tmp_doc[i]);
				i++;
			}
		}printf("\n");
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