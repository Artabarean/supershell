/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:37:20 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/03 11:28:22 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_in(t_redir *redir, int *fin)
{
	if (*fin != -1)
		close(*fin);
	if (find_infile(redir, fin) == 1)
		return (1);
	if (*fin != -1)
	{
		dup2(*fin, 0);
		ft_putendl_fd("debera pasar por aqui", 2);
		close(*fin);
	}
	return (0);
}

int	handle_out(t_redir *redir, int *fout)
{
	if (*fout != -1)
		close(*fout);
	if (find_outfile(redir, fout) == 1)
		return (1);
	if (*fout != -1)
	{
		dup2(*fout, 1);
		ft_putendl_fd("debera pasar por aqui", 2);
		close(*fout);
	}
	return (0);
}

int	handle_hdoc(t_cmd *copy, int *fin)
{
	if (*fin != -1)
		close(*fin);
	if (find_heredoc(copy, fin) == 1)
		return (1);
	if (*fin != -1)
	{
		dup2(*fin, 0);
		close(*fin);
	}
	return (0);
}
