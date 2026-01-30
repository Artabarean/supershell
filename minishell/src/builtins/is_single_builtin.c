/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_single_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:24:54 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/30 10:45:48 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_lone_builtin(t_cmd *cmd, t_prompt *prompt, int fin, int fout)
{
	if (prompt->n_cmds == 1 && cmd->full_cmd[0] != NULL)
	{
		if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		{
			single_builtin(cmd, prompt, fin, fout);
			return (closepfds(prompt->n_cmds, prompt), 1);
		}
		if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		{
			single_builtin(cmd, prompt, fin, fout);
			return (closepfds(prompt->n_cmds, prompt), 1);
		}
		if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		{
			single_builtin(cmd, prompt, fin, fout);
			return (closepfds(prompt->n_cmds, prompt), 1);
		}
		if (!ft_strcmp(cmd->full_cmd[0], "export"))
		{
			single_builtin(cmd, prompt, fin, fout);
			return (closepfds(prompt->n_cmds, prompt), 1);
		}
	}
	return (0);
}

void	single_builtin(t_cmd *cmd, t_prompt *prompt, int fin, int fout)
{
	int	savein;
	int	saveout;

	savein = dup(0);
	saveout = dup(1);
	run_builtin_son(cmd, &fin, &fout);
	if (!ft_strcmp(cmd->full_cmd[0], "exit"))
	{
		dup2(savein, 0);
		close(savein);
		dup2(saveout, 1);
		close(saveout);
		exit_builtin(cmd, prompt);
	}
	if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		cd(cmd->full_cmd, prompt);
	if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		builtin_unset(cmd->full_cmd, prompt);
	if (!ft_strcmp(cmd->full_cmd[0], "export"))
		export_builtin(prompt, cmd);
	dup2(savein, 0);
	close(savein);
	dup2(saveout, 1);
	close(saveout);
}
