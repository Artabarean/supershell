/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:53:38 by alex              #+#    #+#             */
/*   Updated: 2025/10/20 12:50:10 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	handle_exit(void)
{
	ft_putendl_fd("Error:\nThe number of arguments passed is invalid", 2);
	exit(0);
}

void	error_comm(char *comm, char **freeable, int term_fd)
{
	dup2(term_fd, 1);
	printf("pipex: ");
	printf("%s", strerror(errno));
	printf(": ");
	printf("%s\n", comm);
	freer(freeable);
	exit(127);
}

void	error(char *file, int *p_fd)
{
	close(p_fd[0]);
	close(p_fd[1]);
	printf("pipex: ");
	printf("permission denied: ");
	printf("%s\n", file);
	exit(0);
}

void	error_cl(int *p_fd)
{
	close(p_fd[0]);
	close(p_fd[1]);
	ft_putendl_fd("Error: file descriptor couldn't be opened", 2);
	exit(0);
}

void	error_filen(char *s, int *p_fd)
{
	close(p_fd[0]);
	close(p_fd[1]);
	printf("pipex: ");
	printf("no such file or directory: ");
	printf("%s\n", s);
}
