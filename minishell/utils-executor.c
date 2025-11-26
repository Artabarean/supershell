/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:26:01 by gcollet           #+#    #+#             */
/*   Updated: 2025/11/26 12:53:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_command(t_cmd *cmd, t_prompt *prompt)
{
	t_cmd *copy;

	copy = cmd;
	while (copy)
	{
		if (copy->full_cmd[0] != NULL)
		{
			if (!ft_strchr(copy->full_cmd[0], '/'))
				find_path_no_print(copy, prompt);
		}
		if (copy->full_cmd[0] == NULL)
			exit(0);
		copy = copy->next;
	}
}

void	error(char *s)
{
	ft_putstr_fd("Minishell: ", 2);
	perror(s);
	exit(EXIT_FAILURE);
}

void	execute(char **full_cmd, char *full_path, t_prompt *prompt)
{
	if (!full_path)
		exit(EXIT_FAILURE);
	if (execve(full_path, full_cmd, prompt->enviroment->envp) == -1)
		error(full_cmd[0]);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

int	pipecount(t_prompt prompt)
{
	t_cmd	*node_num;
	int		i;

	i = 0;
	node_num = prompt.cmds;
	while (node_num)
	{
		node_num = node_num->next;
		i++;
	}
	return (i - 1);
}
