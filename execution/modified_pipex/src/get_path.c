/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:45:22 by alex              #+#    #+#             */
/*   Updated: 2025/10/20 12:43:34 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_environments(char *name, char **envp)
{
	int		i;
	int		j;
	char	*comp;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		comp = ft_substr(envp[i], 0, j);
		if (ft_strcmp(comp, name) == 0)
		{
			free(comp);
			return (envp[i] + j + 1);
		}
		free(comp);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp, char **freecom, int term_fd)
{
	int		i;
	char	*full_path;
	char	**paths;
	char	*exec;
	char	**cmd_com;

	i = -1;
	paths = ft_split(get_environments("PATH", envp), ':');
	if (!paths)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (error_comm(cmd, freecom, term_fd), NULL);
	}
	cmd_com = ft_split(cmd, ' ');
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(full_path, cmd_com[0]);
		free(full_path);
		if (access(exec, F_OK | X_OK) == 0)
			return (freer(paths), freer(cmd_com), exec);
		free(exec);
	}
	return (freer(paths), freer(cmd_com), error_cmd(cmd, freecom, term_fd), NULL);
}
