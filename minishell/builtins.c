/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:58:47 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/23 14:25:39 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
			export_builtin(prompt ,cmd);
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
//He cambiado la función para utilizar la nueva estructura redir
void	run_builtin_son(t_cmd *cmd, int fin, int fout)
{
	t_cmd	*copy;

	copy = cmd;
	while (copy->redir != NULL)
	{
		if (copy->redir->type == T_REDIR_OUT)
		{
			ft_putendl_fd(copy->redir->file, 2);
			find_outfile(copy, copy->redir, &fout);
		}
		if (copy->redir->type == T_REDIR_IN)
		{
			ft_putendl_fd(copy->redir->file, 2);
			find_infile(copy, copy->redir, &fin);
			
		}
		if (copy->redir->type == T_HEREDOC)
		{
			find_heredoc(copy, copy->redir, &fin);
		}
		copy->redir = copy->redir->next;
	}
}
//	Para ajustar la función a la norma se puede utilizar la variable cmd->max_tkns 
//	para guardar n_cmds?
//	No estás teniendo encuenta lo que devuelven las funciones para cambiar el g_exit_status?
//	if(exit_builtin(cmd, prompt) == 1)
//		perror...

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
		export_builtin(prompt ,cmd);
	else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		exit (builtin_unset(cmd->full_cmd, prompt));
	else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		cd(cmd->full_cmd, prompt);
	else if (!ft_strcmp(cmd->full_cmd[0], "exit"))
	{
		exit_builtin(cmd, prompt);
		return (1);
	}
	return (0);
}
