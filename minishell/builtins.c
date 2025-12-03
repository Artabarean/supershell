/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:58:47 by atabarea          #+#    #+#             */
/*   Updated: 2025/12/03 11:41:00 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
int	builtin_no_in_out (int n_cmds, t_cmd *cmd, t_prompt *prompt)
{
	if (n_cmds == 1)
	{
		if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		{
			exit_builtin(cmd, prompt);
			return (1);
		}
		//else if (!ft_strcmp(cmd->full_cmd[0], "export"))
		//export(cmd->full_cmd);
		else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
	    	return (builtin_unset(cmd->full_cmd, prompt));
		//else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		//cd(cmd->full_cmd, prompt);
	}
    return (0);
}

void	run_builtin_son(t_cmd *cmd, int fin, int fout)
{
	t_cmd	*copy;
	int		i;

	i = 0;
	copy = cmd;
	while (copy)
	{
		while (copy->outfile[i])
		{
			find_outfile(copy, i, &fout);
			i++;
		}
		i = 0;
		while (copy->infile[i])
		{
			find_infile(copy, i, &fin);
			i++;
		}
		i = 0;
		copy = copy->next;
	}
}

int	single_builtin(int n_cmds, t_cmd *cmd, t_prompt *prompt, int fin, int fout)
{
	if (n_cmds == 1)
	{
		if (!ft_strcmp(cmd->full_cmd[0], "exit"))
        {
			run_builtin_son(cmd, fin, fout);
			exit_builtin(cmd, prompt);
            return (1);
        }
		// if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		// {
		// 	run_builtin_son(cmd, fin, fout);
		// 	// 	cd(cmd->full_cmd, prompt);
		// 	return (1);
		// }
		if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		{
			run_builtin_son(cmd, fin, fout);
			exit (builtin_unset(cmd->full_cmd, prompt));
		}
		// if (!ft_strcmp(cmd->full_cmd[0], "export"))
		// {
		// 	run_builtin_son(cmd, fin, fout);
		// 	//     export(cmd->full_cmd);
		// 	return (1);
		// }
	}
    return (0);
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

void	run_builtin_child(t_cmd *cmd, t_prompt *prompt)
{
	if (!ft_strcmp(cmd->full_cmd[0], "echo"))
		echo(cmd->full_cmd);
	else if (!ft_strcmp(cmd->full_cmd[0], "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->full_cmd[0], "env"))
		env(prompt, cmd->full_cmd);
	// else if (!ft_strcmp(cmd->full_cmd[0], "export"))
	//     export(cmd->full_cmd);
	else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
	    exit (builtin_unset(cmd->full_cmd, prompt));
	// else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
	// 	cd(cmd->full_cmd, prompt);
	else if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		exit_builtin(cmd, prompt);
	exit(0);
}
