/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:51:43 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/09 17:23:40 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tmpdoc(t_cmd *cmd)
{
	t_cmd	*copy;
	int		i;

	i = 0;
	copy = cmd;
	while (copy)
	{
		if (copy->tmp_doc)
		{
			while(copy->tmp_doc[i])
			{
				free(copy->tmp_doc[i]);
				i++;
			}
			free(copy->tmp_doc);
			i = 0;
		}
		copy = copy->next;
	}
}

void	set_hdoc_child(t_cmd *cmd, int *fd, t_prompt *prompt)
{
	g_sign = 0;
	set_signal(SIG_HEREDOC);
	heredoc_child(cmd, fd, prompt);
	closehfd(fd);
	free_tmpdoc(cmd);
	free_env(prompt->enviroment);
	free_input(prompt);
	if (g_sign == 130)
		exit (130);
	exit(0);
}
