/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:08:59 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/04 12:28:02 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	freer(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
}

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

void	find_path(t_prompt prompt)
{
	int		i;
	char	**paths;
	int		j;

	j = 0;
	i = -1;
	paths = ft_split(get_environments("PATH", prompt.enviroment->envp), ':');
	if (!paths)
	{
		while(prompt.cmds->full_cmd[j])
		{
			if (access(prompt.cmds->full_cmd[j], F_OK | X_OK) == 0)
				return ;
			printf("error aquí%s\n", prompt.cmds->full_cmd[j]);
			return ;
			j++;
		}
	}
	while (paths[++i])
	{
		prompt.cmds->full_path = ft_strjoin(paths[i], "/");
		prompt.cmds->full_path = ft_strjoin(prompt.cmds->full_path, prompt.cmds->full_cmd[0]);
		if (access(prompt.cmds->full_path, F_OK | X_OK) == 0)
			return ;
	}
	printf("error aquí%s\n", prompt.cmds->full_cmd[j]);
}


