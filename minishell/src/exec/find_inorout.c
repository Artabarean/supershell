/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inorout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:21:31 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/28 16:06:27 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirout(t_redir *redir)
{
	t_redir	*copyrdr;

	copyrdr = redir;
	while (copyrdr != NULL)
	{
		if (copyrdr->type == T_REDIR_OUT || copyrdr->type == T_APPEND)
		{
			return (1);
		}
		copyrdr = copyrdr->next;
	}
	return (0);
}

int	redirin(t_redir *redir)
{
	t_redir	*copyrdr;

	copyrdr = redir;
	while (copyrdr != NULL)
	{
		if (copyrdr->type == T_REDIR_IN)
		{
			return (1);
		}
		copyrdr = copyrdr->next;
	}
	return (0);
}

int	find_outfile(t_redir *redir, int *fileout)
{
	t_redir	*copyrdr;

	copyrdr = redir;
	if (copyrdr->type == T_APPEND)
	{
		*fileout = open_file(copyrdr->file, 0);
		if (*fileout == -1)
			return (1);
	}
	else
	{
		*fileout = open_file(copyrdr->file, 1);
		if (*fileout == -1)
			return (1);
	}
	return (0);
}

int	find_infile(t_redir *redir, int *filein)
{
	t_redir	*copyrdr;

	copyrdr = redir;
	*filein = open_file(copyrdr->file, 2);
	if (*filein == -1)
		return (1);
	return (0);
}

int	find_heredoc(t_cmd *cmd, int *filein)
{
	int		last;

	last = count_strs(cmd->tmp_doc) - 1;
	*filein = open_file(cmd->tmp_doc[last], 2);
	if (*filein == -1)
		return (1);
	return (0);
}
