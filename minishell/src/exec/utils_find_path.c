/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_find_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:22:43 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/10 11:54:16 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_for_child(t_prompt *prompt)
{
	free_input(prompt);
	free_env(prompt->enviroment);
	free(prompt->pid);
}

int	check_access(char *full_cmd, t_prompt *prompt)
{
	if (access(full_cmd, F_OK) == -1)
		prompt->exit_status = 127;
	else if (access(full_cmd, X_OK) == -1)
    	prompt->exit_status = 126;
	return (1);
}

void	exec_if_nondir(t_cmd *cmd, t_prompt *prompt, int n_cmds)
{
	if (find_path_no_print(cmd, prompt) == 1 && ispath(prompt) == 1)
	{
		cmd->full_path = ft_strdup(cmd->full_cmd[0]);
		closepfds(n_cmds, prompt);
		execute(cmd->full_cmd, cmd->full_path, prompt);
	}
}
