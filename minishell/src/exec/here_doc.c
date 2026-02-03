/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:50:00 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/03 16:28:45 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_heredoc(char **tmp_doc)
{
	int	fd;
	int	i;

	i = 0;
	if (tmp_doc)
	{
		while (tmp_doc[i] != NULL)
			i++;
		fd = open(tmp_doc[i - 1], O_RDONLY);
		if (fd == -1)
			return (-1);
		return (fd);
	}
	return (1);
}

char	*createfile(int index)
{
	char	*filename;
	char	*idx;

	idx = ft_itoa(index);
	filename = ft_strjoin("heredoc_", idx);
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		index++;
		filename = ft_strjoin("heredoc_", idx);
	}
	free(idx);
	return (filename);
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

char	*do_single_heredoc(char *limiter, t_env *env, int index)
{
	char	*line;
	char	*filename;
	int		fd;

	filename = createfile(index);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		fd_failed_hd(filename);
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
	return (close(fd), filename);
}

int	process_heredocs(t_cmd *copycmd, t_env *env)
{
	t_redir	*r;
	int		i;

	i = 0;
	if (!copycmd->redir)
		return (0);
	r = copycmd->redir;
	while (r)
	{
		if (r->type == T_HEREDOC)
		{
			if (!copycmd->tmp_doc)
				copycmd->tmp_doc = count_heredoc(copycmd->redir);
			set_signal(SIG_HEREDOC);
			copycmd->tmp_doc[i] = do_single_heredoc(r->file, env, i);
			i++;
		}
		r = r->next;
	}
	if (i == 0)
		return (0);
	return (1);
}
