/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:30 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/23 14:24:24 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	pid_stat(t_cmd *curr_nde, t_prompt *prompt, int last_status)
{
	int	i;
	int	n_cmds;
	int	wstatus;

	i = 0;
	n_cmds = pipecount(*prompt) + 1;
	wstatus = 0;
	while (i < n_cmds && curr_nde)
	{
		set_signal(SIG_WAIT);
		waitpid(prompt->pid[i], &wstatus, 0);
		if (checkfather_builtin(curr_nde) == 0)
		{
			if (curr_nde->next == NULL)
			{
				if (WIFEXITED(wstatus))
					last_status = WEXITSTATUS(wstatus);
				else if (WIFSIGNALED(wstatus))
				{
					last_status = 128 + WTERMSIG(wstatus);
					if(WTERMSIG(wstatus) == SIGQUIT)
						write(2, "Quit (core dumped)\n", 19);
					if(WTERMSIG(wstatus) == SIGINT)
						write(1, "\n", 1);
				}
			}
		}
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
	{
		g_exit_status = 0;
		return ;
	}
	pfd_alloc(prompt, prompt->n_cmds);
	create_pipes(prompt, prompt->n_cmds);
	while (i < prompt->n_cmds && cmd)
	{
		if (cmd->redir && cmd->redir->type == T_HEREDOC)
		{
			process_heredocs(cmd, prompt->enviroment);
			fin = get_last_heredoc(cmd->tmp_doc);
			if (fin == -1)
			{
				closepfds(prompt->n_cmds, prompt);
				return ;
			}
		}
		selectprocess(prompt, cmd, i, &fin, &fout);
		check_error(prompt, i);
		cmd = cmd->next;
		i++;
	}
	closepfds(prompt->n_cmds, prompt);
}

void	file_opener(t_prompt *prompt, t_cmd *cmd, int *fileout, int *filein)
{
	t_redir	*copyrdr;

	copyrdr = cmd->redir;	
	while(copyrdr != NULL)
	{
		if (copyrdr->type == T_REDIR_OUT || copyrdr->type == T_APPEND)
		{
			find_outfile(cmd, copyrdr, fileout); 
		}
		if (copyrdr->type == T_REDIR_IN)
		{
			find_infile(cmd, copyrdr, filein);
		}
		if (copyrdr->type == T_HEREDOC)
		{
			find_heredoc(cmd, copyrdr, filein);
		}
		copyrdr = copyrdr->next;
	}
	check_command(cmd, prompt);
}

void	check_status(int exit_code)
{
//	printf("Exited with code %d\n", exit_code);
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
