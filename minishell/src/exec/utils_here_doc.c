/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:40:27 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/04 17:24:37 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*count_hfds(t_redir *redir)
{
	t_redir	*copy;
	int		count;
	int		*fd;

	count = 0;
	copy = redir;
	while (copy)
	{
		if (copy->type == T_HEREDOC)
			count++;
		copy = copy->next;
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
