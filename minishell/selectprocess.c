/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:59:00 by atabarea          #+#    #+#             */
/*   Updated: 2025/12/02 12:29:55 by atabarea         ###   ########.fr       */
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
	int last;
	int hd_fd;

	n_cmds = pipecount(*prompt) + 1;
	prompt->pid[i] = fork();
	if (prompt->pid[i] == -1)
		error("fork");
	if (prompt->pid[i] == 0)
	{
		file_opener(cmd, fout, fin);
		if (cmd->heredoc && cmd->heredoc[0])
		{
			last = count_strs(cmd->here_doc) - 1;
			printf("cmd->heredoc[%d]: %s\n", last, cmd->here_doc[last]);
			hd_fd = open(cmd->here_doc[last], O_RDONLY);
			if (hd_fd == -1)
				error("heredoc open failed");
			dup2(hd_fd, 0);
			close(hd_fd);
			dup2(0, *fin);
		}
		check_command(cmd, prompt);
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
		exit(0);
	}
}
