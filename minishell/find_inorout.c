/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inorout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:21:31 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/12 14:11:37 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	find_outfile(t_cmd *cmd, int *fileout)
{
	t_redir *copyrdr;

	copyrdr = cmd->redir;
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

void	find_infile(t_cmd *cmd, int *filein)
{
	t_redir	*copyrdr;

	copyrdr = cmd->redir;
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
