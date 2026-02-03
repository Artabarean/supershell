/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:48:09 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/03 17:39:35 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	forker(t_prompt *prompt, int i)
{
	prompt->pid[i] = fork();
	if (prompt->pid[i] == -1)
		error("Fork failed");
}

void	pfd_alloc(t_prompt *prompt, int n_cmds)
{
	int	i;

	i = 0;
	prompt->pfd = malloc(sizeof(int *) * (n_cmds - 1));
	if (!prompt->pfd)
		error("Malloc failed");
	prompt->error_msg = malloc(sizeof(char *) * n_cmds);
	while (i < n_cmds)
	{
		prompt->error_msg[i] = NULL;
		i++;
	}
}

void	closepfds(int n_cmds, t_prompt *prompt)
{
	int	i;

	i = 0;
	while (i < (n_cmds - 1))
	{
		if (prompt->pfd[i][1] != -1)
		{
			close(prompt->pfd[i][1]);
			prompt->pfd[i][1] = -1;
		}
		if (prompt->pfd[i][0] != -1)
		{
			close(prompt->pfd[i][0]);
			prompt->pfd[i][0] = -1;
		}
		i++;
	}
	if (prompt->error_msg)
		free(prompt->error_msg);
	free(prompt->pfd);
}

void	child_process(t_cmd *cmd, t_prompt *prompt, int i, int n_cmds)
{
	if (i > 0)
		dup2(prompt->pfd[i - 1][0], 0);
	if (i < n_cmds - 1)
		dup2(prompt->pfd[i][1], 1);
	if (is_builtin(cmd))
	{
		closepfds(n_cmds, prompt);
		run_builtin_child(cmd, prompt);
		exit(0);
	}
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path_no_print(cmd, prompt) == 1 && ispath(prompt) == 1)
		{
			cmd->full_path = cmd->full_cmd[0];
			closepfds(n_cmds, prompt);
			execute(cmd->full_cmd, cmd->full_path, prompt);
		}
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	closepfds(n_cmds, prompt);
	if (find_path_no_print(cmd, prompt) == 0)
		execute(cmd->full_cmd, cmd->full_path, prompt);
	exit(127);
}

int	execute_(t_cmd *cmd, t_prompt *prompt)
{
	int	i;

	i = 0;
	prompt->n_cmds = pipecount(*prompt) + 1;
	pfd_alloc(prompt, prompt->n_cmds);
	if (builtin_no_in_out(pipecount(*prompt), cmd, prompt) == 1)
		return (closepfds(prompt->n_cmds, prompt), 1);
	check_com(cmd, prompt);
	create_pipes(prompt, prompt->n_cmds);
	while (i < prompt->n_cmds && cmd)
	{
		forker(prompt, i);
		if (prompt->pid[i] == 0)
		{
			set_signal(SIG_CHILD);
			child_process(cmd, prompt, i, prompt->n_cmds);
		}
		else
			find_path(cmd, prompt, i);
		check_error(prompt, i);
		i++;
		cmd = cmd->next;
	}
	return (closepfds(prompt->n_cmds, prompt), 0);
}
