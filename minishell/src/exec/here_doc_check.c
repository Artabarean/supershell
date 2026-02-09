/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:14:33 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/09 17:16:05 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	eof_warning_msg(char *line, char *limiter)
{
	if (!line)
	{
		printf("minishell: warning: here-document \
delimited by end-of-file (wanted `%s')\n", limiter);
			return (1);
	}
	return (0);
}

void	fd_failed_hd(char *filename)
{
	free(filename);
	error_in_child("tmpfile failure");
}

char	*expand_for_heredoc(char *str, t_prompt *prompt)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '$')
		{
			result = extract_char(result, str[i]);
			i++;
			continue ;
		}
		result = expand_dollar(result, str, &i, prompt);
	}
	free(str);
	return (result);
}

int	handle_heredoc(t_prompt *prompt, t_cmd *cmd)
{
	t_cmd	*copycmd;
	t_redir	*rdr;
	int		is_heredoc;

	is_heredoc = 0;
	copycmd = cmd;
	while (copycmd)
	{
		rdr = copycmd->redir;
		while (rdr)
		{
			if (rdr && rdr->type == T_HEREDOC)
			{
				is_heredoc = 1;
				break ;
			}
			rdr = rdr->next;
		}
		copycmd = copycmd->next;
	}
	if (see_if_heredoc(cmd, prompt, is_heredoc) == 1)
		return (1);
	return (0);
}

char	**count_heredoc(t_redir *redir)
{
	t_redir	*copy;
	int		count;
	char	**sizer;

	count = 0;
	copy = redir;
	while (copy)
	{
		if (copy->type == T_HEREDOC)
			count++;
		copy = copy->next;
	}
	sizer = ft_calloc(sizeof(char *), count + 1);
	return (sizer);
}
