/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:40:27 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/10 16:06:19 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	see_if_heredoc(t_cmd *cmd, t_prompt *prompt, int is_heredoc)
{
	if (is_heredoc)
	{
		if (process_heredocs(cmd, prompt))
		{
			prompt->exit_status = 130;
			return (1);
		}
	}
	return (0);
}

void	set_tempdoc(t_cmd *cmd)
{
	t_cmd	*copycmd;

	copycmd = cmd;
	while (copycmd)
	{
		copycmd->tmp_doc = count_heredoc(copycmd->redir);
		copycmd = copycmd->next;
	}
}

int	*count_hfds(t_cmd *cmd)
{
	t_redir	*rdr;
	int		count;
	int		*fd;
	t_cmd	*copycmd;

	copycmd = cmd;
	count = 0;
	while (copycmd)
	{
		rdr = copycmd->redir;
		while (rdr)
		{
			if (rdr->type == T_HEREDOC)
				count++;
			rdr = rdr->next;
		}
		copycmd = copycmd->next;
	}
	fd = ft_calloc(sizeof(int), count + 1);
	fd[count] = -2;
	createfile(cmd, fd);
	return (fd);
}

void	closehfd(int *fd)
{
	int	i;

	i = 0;
	while (fd[i] != -2)
	{
		close(fd[i]);
		i++;
	}
	free(fd);
}

int	heredoc_open(t_cmd *copycmd, int j)
{
	char	*idx;
	int		i;
	int		fd;
	char	*check;

	i = 0;
	idx = ft_itoa(i);
	check = ft_strjoin("/tmp/heredoc_", idx);
	while (access(check, F_OK) == 0)
	{
		free(idx);
		free(check);
		i++;
		idx = ft_itoa(i);
		check = ft_strjoin("/tmp/heredoc_", idx);
	}
	free(check);
	copycmd->tmp_doc[j] = ft_strjoin("/tmp/heredoc_", idx);
	free(idx);
	unlink(copycmd->tmp_doc[j]);
	fd = open(copycmd->tmp_doc[j], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		fd_failed_hd(copycmd->tmp_doc[j]);
	return (fd);
}
