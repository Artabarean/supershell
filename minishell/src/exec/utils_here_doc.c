/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:40:27 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/04 19:09:11 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_tempdoc(t_cmd *cmd)
{
	t_cmd	*copycmd;
	t_redir	*rdr;

	copycmd = cmd;
	while (copycmd)
	{
		rdr = copycmd->redir;
		while (rdr)
		{
			copycmd->tmp_doc = count_heredoc(rdr);
			rdr = rdr->next;
		}
		copycmd = copycmd->next;
	}
}

int		*count_hfds(t_cmd *cmd)
{
	t_redir	*rdr;
	int		count;
	int		*fd;
	t_cmd	*copycmd;

	copycmd = cmd;
	count = 0;
	while (copycmd)
	{
		rdr = copycmd->redir;
		while (rdr)
		{
			if (rdr->type == T_HEREDOC)
				count++;
			rdr = rdr->next;
		}
		copycmd = copycmd->next;
	}
	fd = ft_calloc(sizeof(int), count + 1);
	fd[count] = -2;
	return (fd);
}

void	closehfd(int *fd)
{
	int	i;

	i = 0;
	while (fd[i] != -2)
	{
		close(fd[i]);
		i++;
	}
	free(fd);
}
