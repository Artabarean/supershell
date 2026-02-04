/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:59:00 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/04 16:18:21 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd(int *fd, int value)
{
	dup2(*fd, value);
	close(*fd);
}

int	count_strs(char	**str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	selectprocess(t_prompt *prompt, t_cmd *cmd, int *fin, int *fout)
{
	int	i;

	i = prompt->iter;
	prompt->pid[i] = fork();
	if (prompt->pid[i] == -1)
		error_in_child("fork");
	if (prompt->pid[i] == 0)
	{
		file_opener(prompt, cmd, fout, fin);
		if ((i == 0 && cmd->full_cmd[0]) || (cmd->redir && redirin(cmd->redir)))
		{
			if (((i + 1) < prompt->n_cmds && !redirout(cmd->redir))
				|| (i == 0 && prompt->n_cmds > 1 && !redirout(cmd->redir)))
				child_processpfd(cmd, *fin, i, prompt);
			else if (i > 0 || (i + 1) == prompt->n_cmds || redirout(cmd->redir))
				child_process1(cmd, *fin, *fout, prompt);
		}
		else if (i > 0 && (i + 1) < prompt->n_cmds)
			child_processmid(cmd, prompt, i);
		else if (i > 0 && (i + 1) == prompt->n_cmds)
			child_processend(cmd, *fout, prompt, i);
		exit(g_exit_status);
	}
	if (!is_builtin(cmd) && cmd->full_cmd[0])
		find_path(cmd, prompt, i);
}
