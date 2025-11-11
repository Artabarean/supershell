/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:48:09 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/11 12:13:04 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	closepfds(int n_cmds, t_prompt prompt)
{
	int	i;

	i = 0;
	while (i < (n_cmds - 1))
	{
		close(prompt.pfd[i][0]);
		close(prompt.pfd[i][1]);
		i++;
	}
}
void	child_process(t_cmd *cmd, t_prompt prompt, int i, int n_cmds)
{
	int	j;

	if (i > 0)
		dup2(prompt.pfd[i - 1][0], 0);
	if (i < n_cmds - 1)
		dup2(prompt.pfd[i][1], 1);
	closepfds(n_cmds, prompt);
	find_path(cmd, &prompt);
	execute(cmd->full_cmd, cmd->full_path, prompt);
	exit(1);
}
void	execute_(t_cmd *cmd, t_prompt prompt)
{
	int		i;
	int		n_cmds;

	i = 0;
	n_cmds = pipecount(prompt) + 1;
	prompt.pfd = malloc(sizeof(int[2]) * (n_cmds - 1));
	if (!prompt.pfd)
		error("malloc");
	while (i < n_cmds - 1)
	{
		if (pipe(prompt.pfd[i]) == -1)
			error("pipe");
		i++;
	}
	i = 0;
	while (i < n_cmds && cmd)
	{
		prompt.pid = fork();
		if (prompt.pid == -1)
			error("fork");
		if (prompt.pid == 0)
			child_process(cmd, prompt, i, n_cmds);
		i++;
		cmd = cmd->next;
	}
	closepfds(n_cmds, prompt);
	while (wait(NULL) > 0)
		;
}
