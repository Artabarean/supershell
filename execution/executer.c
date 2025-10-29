/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:07 by alex              #+#    #+#             */
/*   Updated: 2025/10/29 14:23:49 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	check_builtins(t_prompt prompt)
{
	int		j;

	j = 0;
	while (prompt.cmds->full_cmd[j])
	{
		if (ft_strncmp(prompt.cmds->full_cmd[j], "echo", 4) == 0)
			execv();
		if (ft_strncmp(prompt.cmds->full_cmd[j], "export", 6) == 0)
			return (1);
		if (ft_strncmp(prompt.cmds->full_cmd[j], "exit", 4) == 0)
			return (1);
		if (ft_strncmp(prompt.cmds->full_cmd[j], "env", 3) == 0)
			return (1);
		if (ft_strncmp(prompt.cmds->full_cmd[j], "pwd", 3) == 0)
			return (1);
		if (ft_strncmp(prompt.cmds->full_cmd[j], "cd", 2) == 0)
			return (1);
		if (ft_strncmp(prompt.cmds->full_cmd[j], "unset", 5) == 0)
			return (1);
		j++;
	}
}

void    executer(t_prompt prompt)
{
	check_builtins(prompt);
	if (prompt.cmds->infile && prompt.cmds->outfile)
		pipex(prompt);
	else
		execute(prompt.cmds->full_cmd, prompt.cmds->full_path, prompt);
}
