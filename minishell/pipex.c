/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:54 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/12 14:08:54 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	int	n_cmds;

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
		exit(run_builtin_child(cmd, prompt));
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path_no_print(cmd, prompt) == 1)
			exit(127);
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	execute(cmd->full_cmd, cmd->full_path, prompt);
}

void	child_processmid(t_cmd *cmd, t_prompt *prompt, int i)
{
	int	n_cmds;

	n_cmds = pipecount(*prompt) + 1;
	dup2(prompt->pfd[i - 1][0], 0);
	dup2(prompt->pfd[i][1], 1);
	closepfds(n_cmds, prompt);
	if (is_builtin(cmd))
		exit(run_builtin_child(cmd, prompt));
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path_no_print(cmd, prompt) == 1)
			exit(127);
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	execute(cmd->full_cmd, cmd->full_path, prompt);
}

void	child_processend(t_cmd *cmd, int fout, t_prompt *prompt, int i)
{
	int	n_cmds;

	n_cmds = pipecount(*prompt) + 1;
	dup2(prompt->pfd[i - 1][0], 0);
	if (fout != -1)
	{
		dup2(fout, 1);
		close(fout);
	}
	closepfds(n_cmds, prompt);
	if (is_builtin(cmd))
		exit(run_builtin_child(cmd, prompt));
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path_no_print(cmd, prompt) == 1)
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

	last_status = 0;
	prompt.pid = malloc(sizeof(pid_t) * (pipecount(prompt) + 1));
	current_node = prompt.cmds;
	childprocess_(current_node, &prompt);
	current_node = prompt.cmds;
	last_status = pid_stat(current_node, &prompt, last_status);
	check_status(last_status);
	free(prompt.error_msg);
	cleanup_heredoc_files(prompt.cmds);
}
