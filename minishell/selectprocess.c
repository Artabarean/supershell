/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:59:00 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/23 14:13:34 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_double(char *str1, char *str2)
{
	free(str1);
	free(str2);
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

void	selectprocess(t_prompt *prompt, t_cmd *cmd, int i, int *fin, int *fout)
{
	prompt->pid[i] = fork();
	if (prompt->pid[i] == -1)
		error("fork");
	if (prompt->pid[i] == 0)
	{
		file_opener(prompt, cmd, fout, fin);
		if ((i == 0 && cmd->full_cmd[0]) || (cmd->redir && redirin(cmd->redir)))
		{
			if (((i + 1) < prompt->n_cmds && !redirout(cmd->redir)) || (i == 0 && prompt->n_cmds > 1))
				child_process1(cmd, *fin, prompt->pfd[0][1], prompt);
			else if (i > 0 || (i + 1) == prompt->n_cmds || redirout(cmd->redir))
				child_process1(cmd, *fin, *fout, prompt);
		}
		else if (i > 0 && (i + 1) < prompt->n_cmds)
			child_processmid(cmd, prompt, i);
		else if (i > 0 && (i + 1) == prompt->n_cmds)
			child_processend(cmd, *fout, prompt, i);
		exit(g_exit_status);
	}
	if (!is_builtin(cmd))
		find_path(cmd, prompt, i);
}
