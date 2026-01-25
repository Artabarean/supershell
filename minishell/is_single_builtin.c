/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_single_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:24:54 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/23 14:30:03 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_single_builtin(t_cmd *cmd, t_prompt *prompt, int fin, int fout)
{
	if (prompt->n_cmds == 1 && cmd->full_cmd[0] != NULL)
	{
		if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		{
			single_builtin(cmd, prompt, fin, fout);
			return (1);
		}
		if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		{
			single_builtin(cmd, prompt, fin, fout);
			return (1);
		}
		if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		{
			single_builtin(cmd, prompt, fin, fout);
			return (1);
		}
		if (!ft_strcmp(cmd->full_cmd[0], "export"))
		{
			single_builtin(cmd, prompt, fin, fout);
			return (1);
		}
	}
	return (0);
}

//	Para ajustar la función a la norma se puede utilizar la variable cmd->max_tkns 
//	para guardar n_cmds?
//	No estás teniendo encuenta lo que devuelven las funciones para cambiar el g_exit_status?
//	if(exit_builtin(cmd, prompt) == 1)
//		perror...
void	single_builtin(t_cmd *cmd, t_prompt *prompt, int fin, int fout)
{
	int	savein;
	int	saveout;

	savein = dup(0);
	saveout = dup(1);
	if (!ft_strcmp(cmd->full_cmd[0], "exit"))
	{
		run_builtin_son(cmd, fin, fout);
		exit_builtin(cmd, prompt);
	}
	if (!ft_strcmp(cmd->full_cmd[0], "cd"))
	{
		run_builtin_son(cmd, fin, fout);
		cd(cmd->full_cmd, prompt);
	}
	if (!ft_strcmp(cmd->full_cmd[0], "unset"))
	{
		run_builtin_son(cmd, fin, fout);
		builtin_unset(cmd->full_cmd, prompt);
	}
	if (!ft_strcmp(cmd->full_cmd[0], "export"))
	{
		run_builtin_son(cmd, fin, fout);
		export_builtin(prompt ,cmd);
	}
	dup2(savein, 0);
	dup2(saveout, 1);
}
