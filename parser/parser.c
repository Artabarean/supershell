#include "parser.h"

t_cmd	*create_cmd(t_cmd *lst)
{
	t_cmd	*current;

	current = new_cmd();
	add_cmd_back(&lst, current);
	return (current);
}

void	parser(t_prompt *prompt)
{
	int		i;
	int		j;
	t_cmd	*curr;

	i = 0;
	j = 0;
	curr = create_cmd(prompt->cmds);
	while (prompt->tkns[i] != NULL)
	{
		if (!ft_strncmp (prompt->tkns[i], "|", 1))
		{
			curr->full_cmd[j] = NULL;
			curr = create_cmd(prompt->cmds);
			j = 0;
		}
		else if (!ft_strncmp(prompt->tkns[i], "<", 1))
			curr->infile = ft_strdup(prompt->tkns[++i]);
		else if (!ft_strncmp(prompt->tkns[i], ">", 1))
			curr->outfile = ft_strdup(prompt->tkns[++i]);
		else if (!ft_strncmp(prompt->tkns[i], ">>", 2))
		{
			curr->outfile = ft_strdup(prompt->tkns[++i]);
			curr->append = 1;
		}
		else if (!ft_strncmp(prompt->tkns[i], "<<", 2))
		{
			curr->infile = ft_strdup(prompt->tkns[++i]);
			curr->append = 1;
		}
		else
			curr->full_cmd[j++] = ft_strdup(prompt->tkns[i]);
		i++;
	}
	curr->full_cmd[j] = NULL;
}
