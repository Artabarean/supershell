/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:36:15 by alex              #+#    #+#             */
/*   Updated: 2025/10/20 12:11:43 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	open_file(char *file, int create_or_open, int *p_fd)
{
	int	fd;

	if (create_or_open == 0)
	{
		if (access(file, F_OK) < 0)
			return (-1);
		if (access(file, R_OK) < 0)
			return (error(file, p_fd), -1);
		fd = open(file, O_RDONLY, 0777);
	}
	if (create_or_open == 1)
	{
		if (access(file, F_OK) == 0)
		{
			if (access(file, W_OK) < 0)
				return (error(file, p_fd), -1);
		}
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if (fd == -1)
		error_cl(p_fd);
	return (fd);
}
