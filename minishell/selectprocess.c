/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <artabarean@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:59:00 by atabarea          #+#    #+#             */
/*   Updated: 2025/12/17 09:11:17 by atabarea         ###   ########.fr       */
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
	int	n_cmds;

	n_cmds = pipecount(*prompt) + 1;
	prompt->pid[i] = fork();
	if (prompt->pid[i] == -1)
		error("fork");
	if (prompt->pid[i] == 0)
	{
		file_opener(prompt, cmd, fout, fin);
		//here_doc_check(cmd->tmp_doc, cmd->heredoc, hd_fd, fin);
		if (i == 0 || cmd->infile[0] != NULL)
		{
			if (n_cmds > 1 && i == 0)
				child_process1(cmd, *fin, prompt->pfd[0][1], prompt);
			else
				child_process1(cmd, *fin, *fout, prompt);
		}
		else if (i > 0 && (i + 1) < n_cmds)
			child_processmid(cmd, prompt, i);
		else if (i > 0 && (i + 1) == n_cmds)
			child_processend(cmd, *fout, prompt, i);
		exit(prompt->exit_stat);
	}
	find_path(cmd, prompt, i);
}
