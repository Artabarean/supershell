/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:26:01 by gcollet           #+#    #+#             */
/*   Updated: 2025/11/19 11:46:27 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_error(t_prompt *prompt, char *s)
{
	perror(s);
	prompt->error = errno;
}

void	error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	execute(char **full_cmd, char *full_path, t_prompt *prompt)
{
	if (!full_path)
		error(full_cmd[0]);
	if (execve(full_path, full_cmd, prompt->enviroment->envp) == -1)
		set_error(prompt, full_cmd[0]);
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
