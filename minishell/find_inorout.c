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

void	find_outfile(t_cmd *cmd, int i, int	*fileout)
{
	(void)i;
	if (cmd->redir->type == T_APPEND)
		*fileout = open_file(cmd->redir->file, 0);
	else
		*fileout = open_file(cmd->redir->file, 1);
	if (cmd->redir->next != NULL && cmd->next != NULL)
	{
		close(*fileout);
		*fileout = -1;
	}
}

void	find_infile(t_cmd *cmd, int i, int *filein)
{
	(void)i;
	*filein = open_file(cmd->redir->file, 2);
	if (cmd->redir->next != NULL && cmd->next != NULL)
	{
		close(*filein);
		*filein = -1;
	}
}
