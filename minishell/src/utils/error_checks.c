/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:02:00 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/03 11:14:58 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_command(t_cmd *cmd, t_prompt *prompt, int *fout, int *fin)
{
	t_cmd	*copy;

	copy = cmd;
	while (copy)
	{
		if (is_builtin(copy) == 0)
		{
			if (copy->full_cmd[0] != NULL)
			{
				if (!ft_strchr(copy->full_cmd[0], '/'))
					find_path_no_print(copy, prompt);
			}
			if (copy->full_cmd[0] == NULL)
			{
				if (*fout != -1)
					close(*fout);
				if (*fin != -1)
					close(*fin);
				exit(0);
			}
		}
		copy = copy->next;
	}
}

void	error_no_exit(char *s)
{
	s = ft_strjoin("minishell: ", s);
	perror(s);
	free(s);
}

int	error(char *s)
{
	s = ft_strjoin("minishell: ", s);
	perror(s);
	free(s);
	return (-1);
}

void	error_in_child(char *s)
{
	s = ft_strjoin("minishell: ", s);
	perror(s);
	free(s);
	exit(EXIT_FAILURE);
}
