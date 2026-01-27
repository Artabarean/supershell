/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:58:47 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/27 16:36:27 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_no_in_out(int n_cmds, t_cmd *cmd, t_prompt *prompt)
{
	if (n_cmds == 0 && cmd->full_cmd[0] != NULL)
	{
		if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		{
			exit_builtin(cmd, prompt);
			return (1);
		}
		else if (!ft_strcmp(cmd->full_cmd[0], "export"))
		{
			export_builtin(prompt, cmd);
			return (1);
		}
		else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		{
			builtin_unset(cmd->full_cmd, prompt);
			return (1);
		}
		else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		{
			cd(cmd->full_cmd, prompt);
			return (1);
		}
	}
	return (0);
}

void	run_builtin_son(t_cmd *cmd, int *fin, int *fout)
{
	t_redir	*copyrdr;
	t_cmd	*copy;

	copy = cmd;
	copyrdr = cmd->redir;
	while (copyrdr != NULL)
	{
		if (copyrdr->type == T_REDIR_OUT || copyrdr->type == T_APPEND)
		{
			if (handle_out(copyrdr, fout) == 1)
				return ;
		}
		if (copyrdr->type == T_REDIR_IN)
		{
			if (handle_in(copyrdr, fin) == 1)
				return ;
		}
		if (copyrdr->type == T_HEREDOC)
		{
			if (handle_hdoc(copy, fin) == 1)
				return ;
		}
		copyrdr = copyrdr->next;
	}
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
		return (0);
	if (!ft_strcmp(cmd->full_cmd[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd->full_cmd[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->full_cmd[0], "export"))
		return (1);
	if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->full_cmd[0], "env"))
		return (1);
	if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		return (1);
	return (0);
}

int	run_builtin_child(t_cmd *cmd, t_prompt *prompt)
{
	if (!ft_strcmp(cmd->full_cmd[0], "echo"))
		echo(cmd->full_cmd, prompt->enviroment);
	else if (!ft_strcmp(cmd->full_cmd[0], "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->full_cmd[0], "env"))
		env(prompt, cmd->full_cmd);
	else if (!ft_strcmp(cmd->full_cmd[0], "export"))
		export_builtin(prompt, cmd);
	else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		exit(builtin_unset(cmd->full_cmd, prompt));
	else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		cd(cmd->full_cmd, prompt);
	else if (!ft_strcmp(cmd->full_cmd[0], "exit"))
	{
		exit_builtin(cmd, prompt);
		return (1);
	}
	return (0);
}
