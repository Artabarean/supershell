/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_inorout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:21:31 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/19 12:25:27 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	find_outfile(t_cmd *cmd, int i, int	*fileout)
{
	if (cmd->append == 1)
		*fileout = open_file(cmd->outfile[i], 0);
	else
		*fileout = open_file(cmd->outfile[i], 1);
	if (cmd->outfile[i + 1] != NULL && cmd->next != NULL)
	{
		close(*fileout);
		*fileout = -1;
	}
}

void	find_infile(t_cmd *cmd, int i, int *filein)
{
	*filein = open_file(cmd->infile[i], 2);
	if (cmd->infile[i + 1] != NULL && cmd->next != NULL)
	{
		close(*filein);
		*filein = -1;
	}
}
