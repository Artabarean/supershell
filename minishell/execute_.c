/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:48:09 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/26 12:49:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	forker(t_prompt *prompt, int i)
{
	prompt->pid[i] = fork();
	if (prompt->pid[i] == -1)
		error("Fork failed");
}

void	pfd_alloc(t_prompt *prompt, int n_cmds)
{
	prompt->pfd = malloc(sizeof(int[2]) * (n_cmds - 1));
	if (!prompt->pfd)
		error("Malloc failed");
}

void	closepfds(int n_cmds, t_prompt *prompt)
{
	int	i;

	i = 0;
	while (i < (n_cmds - 1))
	{
		if (prompt->pfd[i][0] != -1)
		{
			close(prompt->pfd[i][0]);
			prompt->pfd[i][0] = -1;
		}
		if (prompt->pfd[i][1] != -1)
		{
			close(prompt->pfd[i][1]);
			prompt->pfd[i][1] = -1;
		}
		i++;
	}
}

void	child_process(t_cmd *cmd, t_prompt *prompt, int i, int n_cmds)
{
	int	j;

	if (i > 0)
		dup2(prompt->pfd[i - 1][0], 0);
	if (i < n_cmds - 1)
		dup2(prompt->pfd[i][1], 1);
	closepfds(n_cmds, prompt);
	if (is_builtin(cmd))
	{
		run_builtin_child(cmd, prompt);
		exit(0);
	}
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path(cmd, prompt) == 1)
		{
			closepfds(n_cmds, prompt);
			exit(127);
		}
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	execute(cmd->full_cmd, cmd->full_path, prompt);
	exit(1);
}

void	execute_(t_cmd *cmd, t_prompt *prompt)
{
	int	i;
	int	n_cmds;

	i = 0;
	n_cmds = pipecount(*prompt) + 1;
	pfd_alloc(prompt, n_cmds);
	if (builtin_no_in_out(pipecount(*prompt), cmd, prompt) == 1)
		return ;
	check_command(cmd, prompt);
	while (i < n_cmds - 1)
	{
		if (pipe(prompt->pfd[i]) == -1)
			error("Pipe failed");
		i++;
	}
	i = 0;
	while (i < n_cmds && cmd)
	{
		forker(prompt, i);
		if (prompt->pid[i] == 0)
			child_process(cmd, prompt, i, n_cmds);
		i++;
		cmd = cmd->next;
	}
	closepfds(n_cmds, prompt);
}
