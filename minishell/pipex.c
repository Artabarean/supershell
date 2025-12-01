/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:54 by alex              #+#    #+#             */
/*   Updated: 2025/12/01 10:36:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	child_process1(t_cmd *cmd, int fin, int fout, t_prompt *prompt)
{
	int	n_cmds;

	ft_putstr_fd("process1\n", 2);
	n_cmds = pipecount(*prompt) + 1;
	if (fin != -1)
	{
		dup2(fin, 0);
		close(fin);
	}
	dup2(fout, 1);
	close(fout);
	closepfds(n_cmds, prompt);
	if (is_builtin(cmd))
		run_builtin_child(cmd, prompt);
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path(cmd, prompt) == 1)
			exit(127);
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	execute(cmd->full_cmd, cmd->full_path, prompt);
}

void	child_processmid(t_cmd *cmd, t_prompt *prompt, int i)
{
	int	n_cmds;

	ft_putstr_fd("processmid\n", 2);
	n_cmds = pipecount(*prompt) + 1;
	dup2(prompt->pfd[i - 1][0], 0);
	dup2(prompt->pfd[i][1], 1);
	closepfds(n_cmds, prompt);
	if (is_builtin(cmd))
		run_builtin_child(cmd, prompt);
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path(cmd, prompt) == 1)
			exit(127);
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	execute(cmd->full_cmd, cmd->full_path, prompt);
}

void	child_processend(t_cmd *cmd, int fout, t_prompt *prompt, int i)
{
	int	n_cmds;

	ft_putstr_fd("processend\n", 2);
	n_cmds = pipecount(*prompt) + 1;
	dup2(prompt->pfd[i - 1][0], 0);
	if (fout != -1)
	{
		dup2(fout, 1);
		close(fout);
	}
	closepfds(n_cmds, prompt);
	if (is_builtin(cmd))
		run_builtin_child(cmd, prompt);
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path(cmd, prompt) == 1)
			exit(127);
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	execute(cmd->full_cmd, cmd->full_path, prompt);
}

void	pipex(t_prompt prompt)
{
	t_cmd	*current_node;
	int		last_status;
	int		fileout;

	fileout = -1;
	last_status = 0;
	prompt.pid = malloc(sizeof(pid_t) * (pipecount(prompt) + 1));
	current_node = prompt.cmds;
	childprocess_(current_node, &prompt);
	current_node = prompt.cmds;
	last_status = pid_stat(current_node, &prompt, last_status);
	check_status(last_status);
	cleanup_heredoc_files(prompt.cmds);
}
