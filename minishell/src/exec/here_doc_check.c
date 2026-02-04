/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:14:33 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/04 16:50:29 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eof_warning_msg(char *limiter)
{
	printf("minishell: warning: here-document \
delimited by end-of-file (wanted `%s')\n", limiter);
}

void	fd_failed_hd(char *filename)
{
	free(filename);
	error_in_child("tmpfile failure");
}

char	*expand_for_heredoc(char *str, t_env *env)
{
	char	*keyword;

	keyword = NULL;
	if (!str || !*str)
		return ("");
	while (env)
	{
		keyword = ft_strjoin("$", env->keyword);
		if (!ft_strcmp(str, keyword))
			return (free(keyword), ft_strdup(env->value));
		free(keyword);
		env = env->next;
	}
	return (str);
}

int	handle_heredoc(t_prompt *prompt, t_cmd *cmd)
{
	t_cmd	*copycmd;
	t_redir	*rdr;

	rdr = cmd->redir;
	copycmd = cmd;
	while (copycmd)
	{
		while (rdr)
		{
			if (copycmd->redir && copycmd->redir->type == T_HEREDOC)
			{
				process_heredocs(copycmd, prompt->enviroment);
				break ;
			}
			rdr = rdr->next;
		}
		copycmd = copycmd->next;
	}
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
