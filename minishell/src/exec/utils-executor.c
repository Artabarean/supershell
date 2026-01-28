/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:26:01 by gcollet           #+#    #+#             */
/*   Updated: 2026/01/28 18:18:51 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_com(t_cmd *cmd, t_prompt *prompt)
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
				closepfds(prompt->n_cmds, prompt);
				exit(0);
			}
		}
		copy = copy->next;
	}
}

void	check_exec_errors(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": Is a directory", 2);
			exit(126);
		}
		if (access(path, X_OK) != 0)
		{
			perror(path);
			exit(126);
		}
	}
}

void	execute(char **full_cmd, char *full_path, t_prompt *prompt)
{
	char	**envp;
	int		err;

	if (!full_path)
		exit(EXIT_FAILURE);
	envp = env_to_envp(prompt->enviroment);
	check_exec_errors(full_path);
	if (execve(full_path, full_cmd, envp) == -1)
	{
		err = errno;
		free_doble_ptr(envp);
		error_no_exit(full_path);
		if (err == ENOENT)
			exit(127);
		else if (err == EACCES)
			exit(126);
		else
			exit(1);
	}
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
