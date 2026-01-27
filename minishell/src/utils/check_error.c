/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 08:04:50 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/27 15:06:05 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_error(t_prompt *prompt, int i)
{
	if (prompt->error_msg)
	{
		if (prompt->error_msg[i])
		{
			write(2, prompt->error_msg[i], ft_strlen(prompt->error_msg[i]));
			free(prompt->error_msg[i]);
		}
	}
}
