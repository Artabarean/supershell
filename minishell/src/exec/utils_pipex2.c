/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:25:37 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/28 18:04:07 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child_processpfd(t_cmd *cmd, int fin, int i, t_prompt *prompt)
{
	if (fin != -1)
	{
		dup2(fin, 0);
		close(fin);
	}
	dup2(prompt->pfd[i][1], 1);
	closepfds(prompt->n_cmds, prompt);
	if (is_builtin(cmd))
		exit(run_builtin_child(cmd, prompt));
	if (!ft_strchr(cmd->full_cmd[0], '/'))
	{
		if (find_path_no_print(cmd, prompt) == 1)
			exit(127);
	}
	else
		cmd->full_path = cmd->full_cmd[0];
	execute(cmd->full_cmd, cmd->full_path, prompt);
}

int	open_file_exit(char *name, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
	{
		file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	else if (i == 2)
	{
		file = open(name, O_RDONLY, 0777);
	}
	if (file == -1)
	{
		error_in_child(name);
	}
	return (file);
}

int	find_outfile_child(t_redir *redir, int *fileout)
{
	t_redir	*copyrdr;

	copyrdr = redir;
	if (copyrdr->type == T_APPEND)
	{
		*fileout = open_file_exit(copyrdr->file, 0);
		if (*fileout == -1)
			return (1);
	}
	else
	{
		*fileout = open_file_exit(copyrdr->file, 1);
		if (*fileout == -1)
			return (1);
	}
	return (0);
}

int	find_infile_child(t_redir *redir, int *filein)
{
	t_redir	*copyrdr;

	copyrdr = redir;
	*filein = open_file_exit(copyrdr->file, 2);
	if (*filein == -1)
		return (1);
	return (0);
}

int	find_heredoc_child(t_cmd *cmd, int *filein)
{
	int		last;

	last = count_strs(cmd->tmp_doc) - 1;
	*filein = open_file_exit(cmd->tmp_doc[last], 2);
	if (*filein == -1)
		return (1);
	return (0);
}
