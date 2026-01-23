/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inorout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:21:31 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/23 12:28:25 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	find_outfile(t_cmd *cmd, t_redir *redir, int *fileout)
{
	t_redir *copyrdr;

	copyrdr = redir;
	if (copyrdr->type == T_APPEND)
		*fileout = open_file(copyrdr->file, 0);
	else
		*fileout = open_file(copyrdr->file, 1);
	if (copyrdr->next != NULL)
	{
		copyrdr = copyrdr->next;
		if (copyrdr->type == T_REDIR_OUT && cmd->next != NULL)
		{
			close(*fileout);
			*fileout = -1;
		}
	}
}

void	find_infile(t_cmd *cmd, t_redir *redir, int *filein)
{
	t_redir	*copyrdr;

	copyrdr = redir;
	*filein = open_file(copyrdr->file, 2);
	if (copyrdr->next != NULL)
	{
		copyrdr = copyrdr->next;
		if (copyrdr->type == T_REDIR_IN && cmd->next != NULL)
		{
			close(*filein);
			*filein = -1;
		}
	}
}

void	find_heredoc(t_cmd *cmd, t_redir *redir, int *filein)
{
	t_redir	*copyrdr;
	int		last;

	copyrdr = redir;
	last = count_strs(cmd->tmp_doc) - 1;
	ft_putendl_fd(cmd->tmp_doc[last], 2);
	*filein = open_file(cmd->tmp_doc[last], 2);
	if (copyrdr->next != NULL)
	{
		copyrdr = copyrdr->next;
		if (copyrdr->type == T_HEREDOC && cmd->next != NULL)
		{
			close(*filein);
			*filein = -1;
		}
	}
}