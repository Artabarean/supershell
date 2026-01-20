/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnofile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:15:54 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/20 10:17:34 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	printnofile(t_prompt *prompt, char *full_cmd, int j)
{
	char	*tmp;
	char	*msg;

	msg = ft_strdup("Minishell: ");
	tmp = msg;
	msg = ft_strjoin(tmp, full_cmd);
	free(tmp);
	tmp = msg;
	msg = ft_strjoin(tmp, ": no such file or directory\n");
	free(tmp);
	prompt->error_msg[j] = msg;
}
