/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:22:09 by atabarea          #+#    #+#             */
/*   Updated: 2025/10/20 12:51:43 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_cmd(char *cmd, char **freecom, int term_fd)
{
	dup2(term_fd, 1);
	printf("pipex: ");
	printf("command not found: ");
	printf("%s\n",cmd);
	freer(freecom);
	exit(127);
}

void	error_commfr(char *comm, char **freeable, int term_fd)
{
	dup2(term_fd, 1);
	printf("pipex: ");
	printf("%s", strerror(errno));
	printf(": ");
	printf("%s\n", comm);
	if (freeable)
		freer(freeable);
	exit(127);
}
