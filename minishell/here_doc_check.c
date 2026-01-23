/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:14:33 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/23 12:41:17 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**count_heredoc(t_redir *redir)
{
	t_redir *copy;
	int		count;
	char	**sizer;

	count = 0;
	copy = redir;
	while(copy)
	{
		if (copy->type == T_HEREDOC)
			count++;
		copy = copy->next;
	}
	sizer = malloc(sizeof(char *) * count);
	sizer[count] = NULL;
	return (sizer);
}

// void	here_doc_check(char **here_doc, int *fin)
// {
// 	int	last;
// 	int	hd_fd;

// 	if (here_doc)
// 	{
// 		last = count_strs(here_doc) - 1;
// 		hd_fd = open(here_doc[last], O_RDONLY);
// 		if (hd_fd == -1)
// 			error("heredoc open failed");
// 		dup2(hd_fd, 0);
// 		close(hd_fd);
// 		dup2(0, *fin);
// 	}
// }
