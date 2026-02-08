/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:50:00 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/06 15:57:31 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	createfile(t_cmd *cmd, int *fd)
{
	int		i;
	int		j;
	int		k;
	t_cmd	*copycmd;
	t_redir	*redir;

	copycmd = cmd;
	k = 0;
	i = 0;
	while (copycmd)
	{
		redir = copycmd->redir;
		j = 0;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				fd[k++] = heredoc_open(copycmd, i, j);
				j++;
				i++;
			}
			redir = redir->next;
		}
		copycmd = copycmd->next;
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
		line = readline("> ");
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
	t_cmd	*copycmd;
	t_redir	*redir;
	int		i;

	copycmd = cmd;
	i = 0;
	while (copycmd)
	{
		redir = copycmd->redir;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				do_single_heredoc(redir->file, env, fd[i]);
				i++;
			}
			redir = redir->next;
		}
		copycmd = copycmd->next;
	}
	return (0);
}

int	process_heredocs(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	int		*fd;

	set_tempdoc(cmd);
	fd = count_hfds(cmd);
	createfile(cmd, fd);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		set_signal(SIG_HEREDOC);
		heredoc_child(cmd, env, fd);
		exit(0);
	}
	set_signal(SIG_WAIT);
	waitpid(pid, &status, 0);
	closehfd(fd);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
			return (130);
		return (WEXITSTATUS(status));
	}
	return (0);
}
