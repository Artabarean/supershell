/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:54 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/10 11:52:54 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_prompt *prompt, int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds - 1)
	{
		if (pipe(prompt->pfd[i]) == -1)
			error("Pipe failed");
		i++;
	}
}

void	child_process1(t_cmd *cmd, int fin, int fout, t_prompt *prompt)
{
	if (fin > 2)
		set_fd(&fin, 0);
	if (fout != -1)
		set_fd(&fout, 1);
	closepfds(prompt->n_cmds, prompt);
	if (is_builtin(cmd))
		exit(run_builtin_child(cmd, prompt));
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path_no_print(cmd, prompt) == 1 && ispath(prompt) == 1)
		{
			cmd->full_path = cmd->full_cmd[0];
			execute(cmd->full_cmd, cmd->full_path, prompt);
		}
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	if (find_path_no_print(cmd, prompt) == 0)
		execute(cmd->full_cmd, cmd->full_path, prompt);
	else
		clean_for_child(prompt);
	exit(prompt->exit_status);
}

void	child_processmid(t_cmd *cmd, t_prompt *prompt, int i)
{
	dup2(prompt->pfd[i - 1][0], 0);
	dup2(prompt->pfd[i][1], 1);
	closepfds(prompt->n_cmds, prompt);
	if (is_builtin(cmd))
		exit(run_builtin_child(cmd, prompt));
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path_no_print(cmd, prompt) == 1 && ispath(prompt) == 1)
		{
			cmd->full_path = cmd->full_cmd[0];
			execute(cmd->full_cmd, cmd->full_path, prompt);
		}
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	if (find_path_no_print(cmd, prompt) == 0)
		execute(cmd->full_cmd, cmd->full_path, prompt);
	else
		clean_for_child(prompt);
	exit(prompt->exit_status);
}

void	child_processend(t_cmd *cmd, int fout, t_prompt *prompt, int i)
{
	dup2(prompt->pfd[i - 1][0], 0);
	if (fout != -1)
	{
		dup2(fout, 1);
		close(fout);
	}
	closepfds(prompt->n_cmds, prompt);
	if (is_builtin(cmd))
		exit(run_builtin_child(cmd, prompt));
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path_no_print(cmd, prompt) == 1 && ispath(prompt) == 1)
		{
			cmd->full_path = cmd->full_cmd[0];
			execute(cmd->full_cmd, cmd->full_path, prompt);
		}
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	if (find_path_no_print(cmd, prompt) == 0)
		execute(cmd->full_cmd, cmd->full_path, prompt);
	else
		clean_for_child(prompt);
	exit(prompt->exit_status);
}

void	pipex(t_prompt *prompt)
{
	t_cmd	*curr_node;

	prompt->pid = ft_calloc(sizeof(pid_t), (pipecount(*prompt) + 1));
	prompt->n_cmds = pipecount(*prompt) + 1;
	curr_node = prompt->cmds;
	childprocess_(curr_node, prompt);
	curr_node = prompt->cmds;
	if (prompt->pid[0] != 0)
		prompt->exit_status = pid_stat(curr_node, prompt, prompt->exit_status);
	set_signal(SIG_PROMPT);
	if (g_sign)
		prompt->exit_status = g_sign;
	check_status(*prompt, prompt->exit_status);
	if (prompt->pid)
		free(prompt->pid);
	cleanup_heredoc_files(prompt->cmds);
}
