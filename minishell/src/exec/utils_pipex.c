/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:30 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/27 16:55:34 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pid_stat(t_cmd *curr_nde, t_prompt *prompt, int last_status)
{
	int	i;
	int	wstatus;

	i = 0;
	wstatus = 0;
	while (i < prompt->n_cmds && curr_nde)
	{
		set_signal(SIG_WAIT);
		waitpid(prompt->pid[i], &wstatus, 0);
		if (checkfather_builtin(curr_nde) == 0)
			is_parent(curr_nde, &wstatus, &last_status);
		else
			last_status = 0;
		curr_nde = curr_nde->next;
		i++;
	}
	return (last_status);
}

void	childprocess_(t_cmd *cmd, t_prompt *prompt)
{
	int	i;
	int	fin;
	int	fout;

	fin = -1;
	fout = -1;
	i = 0;
	if (is_single_builtin(cmd, prompt, fin, fout) == 1)
		return ;
	pfd_alloc(prompt, prompt->n_cmds);
	create_pipes(prompt, prompt->n_cmds);
	while (i < prompt->n_cmds && cmd)
	{
		if (handle_heredoc(prompt, cmd, &fin) == 1)
			return ;
		selectprocess(prompt, cmd, i, &fin, &fout);
		check_error(prompt, i);
		free(cmd->full_path);
		cmd = cmd->next;
		i++;
	}
	free(prompt->error_msg);
	closepfds(prompt->n_cmds, prompt);
}

void	file_opener(t_prompt *prompt, t_cmd *cmd, int *fileout, int *filein)
{
	t_redir	*copyrdr;

	copyrdr = cmd->redir;
	while (copyrdr != NULL)
	{
		if (copyrdr->type == T_REDIR_OUT || copyrdr->type == T_APPEND)
		{
			if (*fileout != -1)
				close(*fileout);
			find_outfile(copyrdr, fileout);
		}
		if (copyrdr->type == T_REDIR_IN)
		{
			if (*filein != -1)
				close(*filein);
			find_infile(copyrdr, filein);
		}
		if (copyrdr->type == T_HEREDOC)
		{
			if (*filein != -1)
				close(*filein);
			find_heredoc(cmd, filein);
		}
		copyrdr = copyrdr->next;
	}
	check_command(cmd, prompt, fileout, filein);
}

void	check_status(int exit_code)
{
	g_exit_status = exit_code;
}

int	open_file(char *name, int i)
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
		error(name);
	return (file);
}
