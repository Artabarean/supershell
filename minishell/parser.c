/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:54 by medel-ca          #+#    #+#             */
/*   Updated: 2025/12/17 09:54:20 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int is_redirection(char *tkn)
{
    return (!ft_strcmp(tkn, "<")
        || !ft_strcmp(tkn, ">")
        || !ft_strcmp(tkn, "<<")
        || !ft_strcmp(tkn, ">>"));
}

bool	parser(t_prompt *prompt, t_cmd *curr, char **tkn)
{
	while (*tkn)
	{
		if (!ft_strncmp(*tkn, "|", 2))
		{
			if (!curr->full_cmd || !curr->full_cmd[0])
			{
				syntax_error("|");
				return (0);
			}
			curr->next = create_cmd(prompt);
			curr = curr->next;
			tkn++;
		}
		else if (is_redirection(*tkn))
		{
			if (!*(tkn + 1) || is_redirection(*(tkn + 1))
                || !ft_strncmp(*(tkn + 1), "|", 2))
            {
                syntax_error(*tkn);
                return (0);
            }
			if (!create_file(&tkn, curr))
			{
				syntax_error(*tkn);
				return (0);
			}
		}
		else
		{
			add_arg_to_cmd(*tkn, curr);
			tkn++;
		}
	}
	if (!curr->full_cmd || !curr->full_cmd[0])
    {
        syntax_error("newline");
        return (0);
    }
	curr->next = NULL;
	return (1);
}

bool	init_parser(t_prompt *prompt)
{
	t_cmd	*curr;
	char	**tkn;

	if (!prompt || !prompt->tkns)
		return (0);
	curr = create_cmd(prompt);
	prompt->cmds = curr;
	tkn = prompt->tkns;
	if (!parser(prompt, curr, tkn))
		return (0);
	return (1);
}
