/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:30 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/06 17:59:44 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pid_stat(t_cmd *curr_nde, t_prompt *prompt, int last_status)
{
	int		i;
	int		wstatus;
	pid_t	pid;

	i = 0;
	wstatus = 0;
	while (i < prompt->n_cmds && curr_nde)
	{
		set_signal(SIG_WAIT);
		if (prompt->pid[0] > 0)
		{
			pid = waitpid(prompt->pid[i], &wstatus, 0);
			if (pid > 0)
			{
				if (WIFSIGNALED(wstatus))
					pid_util(&wstatus, prompt, &last_status, i);
				else if (WIFEXITED(wstatus))
				{
					if (checkfather_builtin(curr_nde) == 0)
						last_status = WEXITSTATUS(wstatus);
					else
						last_status = 0;
				}
				
			}
		}
		curr_nde = curr_nde->next;
		i++;
	}
	return (last_status);
}

void	childprocess_(t_cmd *cmd, t_prompt *prompt)
{
	int	fin;
	int	fout;

	fin = -1;
	fout = -1;
	prompt->iter = 0;
	pfd_alloc(prompt);
	create_pipes(prompt, prompt->n_cmds);
	if (handle_heredoc(prompt, cmd) == 1)
		return ;
	while (prompt->iter < prompt->n_cmds && cmd)
	{
		if (!is_builtin(cmd))
		{
			if(!resolve_and_check(cmd, prompt, prompt->iter))
    		{
				prompt->iter++;
        		cmd = cmd->next;
        		continue;
			}	
		}
		if (prompt->n_cmds == 1 && is_lone_builtin(cmd, prompt, fin, fout) == 1)
			return ;
		if (cmd->full_cmd && cmd->full_cmd[0])
			selectprocess(prompt, cmd, &fin, &fout);
		check_error(cmd, prompt, prompt->iter);
		cmd = cmd->next;
		prompt->iter++;
	}
	if (fin != -1)
		close(fin);
	closepfds(prompt->n_cmds, prompt);
}

void	file_opener(t_prompt *prompt, t_cmd *cmd, int *fileout, int *filein)
{
	t_redir	*copyrdr;

	copyrdr = cmd->redir;
	while (copyrdr != NULL)
	{
		if (copyrdr->type == T_REDIR_OUT || copyrdr->type == T_APPEND)
			find_outfile_child(copyrdr, fileout);
		if (copyrdr->type == T_REDIR_IN)
			find_infile_child(copyrdr, filein);
		if (copyrdr->type == T_HEREDOC)
			find_heredoc_child(cmd, filein);
		copyrdr = copyrdr->next;
	}
	check_command(cmd, prompt, fileout, filein);
}

void	check_status(t_prompt prompt, int exit_code)
{
	(void)prompt;
	prompt.exit_status = exit_code;
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
	{
		return (error(name));
	}
	return (file);
}
