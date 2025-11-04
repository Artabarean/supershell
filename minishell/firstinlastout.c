/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstinlastout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:41:39 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/04 11:53:59 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	firstinlastout(t_cmd *curr_node , int fin, int fout, t_prompt prompt, int i)
{
	int	j;

	j = pipecount(prompt);
	if (j > 0)
	{
		if (fin != -1)
		{
			dup2(prompt.pfd[i][0], fin);
			close(prompt.pfd[i][0]);
		}
		if (fout != -1)
		{
			dup2(prompt.pfd[i][1], fout);
			close(prompt.pfd[i][1]);
		}
	}
	prompt.pid = fork();
	if (prompt.pid == -1)
		error("pid");
	if (prompt.pid == 0)
	{
		printf("fout: %d\n", fout);
		dup2(fout, 1);
		if (check_builtins(prompt) == 1)
			exit(0);
		execute(curr_node->full_cmd, curr_node->full_path, prompt);
	}
}
