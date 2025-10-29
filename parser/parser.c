#include "parser.h"

void	parser(t_prompt *prompt, t_cmd *curr, char **tkn)
{
	while (*tkn)
	{
		if (!ft_strncmp(*tkn, "|", 2))
		{
			curr->next = create_cmd(prompt);
			curr = curr->next;
			tkn++;
		}
		else if (!ft_strncmp(*tkn, ">>", 3) || !ft_strncmp(*tkn, "<<", 3)
			|| !ft_strncmp(*tkn, "<", 2) || !ft_strncmp(*tkn, ">", 2))
		{
			if (!create_file(&tkn, curr))
			{
				perror("Redirección incorrecta");
				return ;
			}
		}
		else
		{
			add_arg_to_cmd(*tkn, curr);
			tkn++;
		}
	}
	curr->next = NULL;
}

void	init_parser(t_prompt *prompt)
{
	t_cmd	*curr;
	char	**tkn;

	if (!prompt || !prompt->tkns)
		return ;
	curr = create_cmd(prompt);
	prompt->cmds = curr;
	tkn = prompt->tkns;
	parser(prompt, curr, tkn);
}
