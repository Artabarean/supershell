/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:48:09 by atabarea          #+#    #+#             */
/*   Updated: 2025/10/30 20:17:41 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	execute_(char **full_cmd, char *full_path, t_prompt prompt)
{
	int	fd[2];

	prompt.pid = fork();
	set_signal(CHILD_EXIT, NULL); // ctrl+C cierra proceso hijo o ctrl+\ cierra la terminal con core dumped
	if (prompt.pid == -1)
		error();
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
