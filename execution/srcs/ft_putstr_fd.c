/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 11:17:23 by gcollet           #+#    #+#             */
/*   Updated: 2025/10/22 11:25:24 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Écrit la chaine de caractères ’s’ sur le file descriptor donné. */

#include "../libft/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}
