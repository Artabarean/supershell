/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:50:00 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/04 17:28:12 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	createfile(t_cmd *cmd, int *fd)
{
	char	*idx;
	int		i;
	int		j;
	t_redir	*rdr;

	i = 0;
	j = 0;
	rdr = cmd->redir;
	while (rdr)
	{
		if (rdr->type == T_HEREDOC)
		{
			idx = ft_itoa(i);
			cmd->tmp_doc[j] = ft_strjoin("heredoc_", idx);
			free(idx);
			if (access(cmd->tmp_doc[j], F_OK) != 0)
			{
				fd[j] = open(cmd->tmp_doc[j], O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (fd[j] == -1)
					fd_failed_hd(cmd->tmp_doc[j]);
				j++;
			}
		}
		i++;
		rdr = rdr->next;
	}
}


void	cleanup_heredoc_files(t_cmd *cmds)
{
	t_cmd	*c;
	int		i;

	c = cmds;
	while (c)
	{
		if (c->tmp_doc)
		{
			i = 0;
			while (c->tmp_doc[i])
			{
				unlink(c->tmp_doc[i]);
				free(c->tmp_doc[i]);
				i++;
			}
			free(c->tmp_doc);
		}
		c = c->next;
	}
}

void	do_single_heredoc(char *limiter, t_env *env, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("< ");
		if (!line)
		{
			eof_warning_msg(limiter);
			break ;
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(expand_for_heredoc(line, env), fd);
		free(line);
	}
	close(fd);
}

static int	heredoc_child(t_cmd *cmd, t_env *env, int *fd)
{
	t_redir	*r;
	int		i;

	i = 0;
	r = cmd->redir;
	while (r)
	{
		if (r->type == T_HEREDOC)
		{
			do_single_heredoc(r->file, env, fd[i]);
			i++;
		}
		r = r->next;
	}
	return (0);
}


int	process_heredocs(t_cmd *copycmd, t_env *env)
{
	pid_t	pid;
	int		status;
	int		*fd;

	copycmd->tmp_doc = count_heredoc(copycmd->redir);
	fd = count_hfds(copycmd->redir);
	if (!copycmd->tmp_doc)
		return (0);
	createfile(copycmd, fd);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		set_signal(SIG_HEREDOC);
		heredoc_child(copycmd, env, fd);
		exit(0);
	}
	set_signal(SIG_WAIT);
	waitpid(pid, &status, 0);
	closehfd(fd);
	if (WIFSIGNALED(status))
		return (g_exit_status = 130, 1);
	return (0);
}
