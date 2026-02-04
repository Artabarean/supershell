/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 08:04:50 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/04 17:46:14 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_error(t_cmd *cmd, t_prompt *prompt, int i)
{
	if (prompt->error_msg && prompt->error_msg[i])
	{
		write(2, prompt->error_msg[i], ft_strlen(prompt->error_msg[i]));
		free(prompt->error_msg[i]);
		if (cmd->full_path)
			free(cmd->full_path);
	}
}
