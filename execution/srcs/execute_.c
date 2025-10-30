/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:48:09 by atabarea          #+#    #+#             */
/*   Updated: 2025/10/30 19:19:34 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_(char **full_cmd, char *full_path, t_prompt prompt)
{
	int	fd[2];

	prompt.pid = fork();
	if (prompt.pid == -1)
		return (error);
	if (prompt.pid == 0)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		if (!full_path)
			error();
		if (execve(full_path, full_cmd, prompt.enviroment->envp) == -1)
			error();
	}
}
