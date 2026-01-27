/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inorout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:21:31 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/27 15:07:17 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirout(t_redir *redir)
{
	t_redir *copyrdr;

	copyrdr = redir;
	while (copyrdr != NULL)
	{
		if (copyrdr->type == T_REDIR_OUT)
		{
			return(1);
		}
		copyrdr = copyrdr->next;
	}
	return (0);
}

int	redirin(t_redir *redir)
{
	t_redir *copyrdr;

	copyrdr = redir;
	while (copyrdr != NULL)
	{
		if (copyrdr->type == T_REDIR_IN)
		{
			return(1);
		}
		copyrdr = copyrdr->next;
	}
	return (0);
}

int	find_outfile(t_redir *redir, int *fileout)
{
	t_redir *copyrdr;

	copyrdr = redir;
	if (copyrdr->type == T_APPEND)
	{
		if (open_file(copyrdr->file, 0) == -1)
			return (1);
		*fileout = open_file(copyrdr->file, 0);
	}
	else
	{
		if (open_file(copyrdr->file, 1) == -1)
			return (1);
		*fileout = open_file(copyrdr->file, 1);
	}
	return (0);
}

int	find_infile(t_redir *redir, int *filein)
{
	t_redir	*copyrdr;

	copyrdr = redir;
	if (open_file(copyrdr->file, 2) == -1)
		return (1);
	*filein = open_file(copyrdr->file, 2);
	return (0);
}

int	find_heredoc(t_cmd *cmd, int *filein)
{
	int		last;

	last = count_strs(cmd->tmp_doc) - 1;
	if (open_file(cmd->tmp_doc[last], 2) == -1)
		return (1);
	*filein = open_file(cmd->tmp_doc[last], 2);
	return (0);
}
