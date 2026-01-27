/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnofile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:15:54 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/27 15:08:01 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
