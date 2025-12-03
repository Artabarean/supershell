/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:14:33 by atabarea          #+#    #+#             */
/*   Updated: 2025/12/03 12:25:22 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	here_doc_check(char **here_doc, char **heredoc, int hd_fd, int *fin)
{
	int	last;

	if (heredoc && heredoc[0])
	{
		last = count_strs(here_doc) - 1;
		hd_fd = open(here_doc[last], O_RDONLY);
		if (hd_fd == -1)
			error("heredoc open failed");
		dup2(hd_fd, 0);
		close(hd_fd);
		dup2(0, *fin);
	}
}
