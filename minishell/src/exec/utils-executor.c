/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:26:01 by gcollet           #+#    #+#             */
/*   Updated: 2026/02/06 17:50:30 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ispath(t_prompt *prompt)
{
	t_env	*copyenv;

	copyenv = prompt->enviroment;
	while (copyenv)
	{
		if (!ft_strcmp(copyenv->keyword, "PATH"))
		{
			if (copyenv->value != NULL)
				return (0);
		}
		copyenv = copyenv->next;
	}
	return (1);
}

void	check_com(t_cmd *cmd, t_prompt *prompt)
{
	t_cmd	*copy;

	copy = cmd;
	while (copy)
	{
		if (is_builtin(copy) == 0)
		{
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
		else if (access(path, X_OK) != 0)
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

	envp = env_to_array(prompt->enviroment);
	check_exec_errors(full_path);
	if (execve(full_path, full_cmd, envp) == -1)
	{
		err = errno;
		free_doble_ptr(envp);
		error_no_exit(full_cmd[0]);
		if (err == ENOENT)
			exit(127);
		else if (err == EACCES)
			exit(126);
		else
			exit(1);
	}
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
