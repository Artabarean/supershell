/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:50:00 by atabarea          #+#    #+#             */
/*   Updated: 2025/12/03 13:03:07 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*createfile(char *filename, int index)
{
	filename = ft_strjoin("heredoc_", ft_itoa(index));
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		index++;
		filename = ft_strjoin("heredoc_", ft_itoa(index));
	}
	return (filename);
}

char	*expand_variables(char *line, t_env *env)
{
	int		i;
	char	*res;
	char 	*var;
	char	*tmp;
	char 	c[2];
	int		j;
	t_env	*e;

	i = 0;
	res	= ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && ft_isalnum(line[i + 1]))
		{
			j = i + 1;
			while (ft_isalnum(line[j]))
				j++;
			var = ft_substr(line, i + 1, j - (i + 1));
			e = env;
			while (e && ft_strcmp(e->keyword, var) != 0)
				e = e->next;
			tmp = res;
			if (e)
				res = ft_strjoin(res, e->value);
			else
				res = ft_strjoin(res, "");
			free(tmp);
			free(var);
			i = j;
		}
		else
		{
			c[0] = line[i];
			c[1] = 0;
			tmp = res;
			res = ft_strjoin(res, c);
			free(tmp);
			i++;
		}
	}
	return (res);
}

void cleanup_heredoc_files(t_cmd *cmds)
{
	t_cmd	*c; 
	int 	i;

	c = cmds;
	while (c)
	{
		if (c->here_doc)
		{
			i = 0;
			while (c->here_doc[i])
			{
				unlink(c->here_doc[i]);
				free(c->here_doc[i]);
				i++;
			}
			free(c->here_doc);
		}
		c = c->next;
	}
}

char	*do_single_heredoc(char *limiter, t_env *env, int index, t_cmd *cmd)
{
	char	*line;
	char	*expanded;
	char	*filename;

	filename = createfile(filename, index);
	int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		error("heredoc tmpfile");
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break;
		}
		expanded = expand_variables(line, env);
		ft_putendl_fd(expanded, fd);
		free_double(expanded, line);
	}
	close(fd);
	return (ft_strdup(filename));
}

int	process_heredocs(t_cmd *cmd, t_env *env)
{
	int i;
	int count;

	if (!cmd->heredoc)
		return (0);
	count = count_strs(cmd->heredoc);
	cmd->here_doc = malloc(sizeof(char *) * (count + 1));
	if (!cmd->here_doc)
		error("malloc heredoc");
	i = 0;
	while (cmd->heredoc[i])
	{
		printf("heredoc[%d]: %s\n", i, cmd->heredoc[i]);
		cmd->here_doc[i] = do_single_heredoc(cmd->heredoc[i], env, i, cmd);
		i++;
	}
	cmd->here_doc[i] = NULL;
	return (1);
}
