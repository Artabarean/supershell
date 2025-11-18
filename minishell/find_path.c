/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:08:59 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/17 11:31:45 by atabarea         ###   ########.fr       */
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

char	*get_environments(char *name, t_prompt *prompt)
{
	t_env 	*curr_env;
	char	*path;

	curr_env = prompt->enviroment; 
	while (curr_env)
	{
		if (!ft_strcmp(name, curr_env->keyword))
			path = curr_env->value;
		curr_env = curr_env->next;
	}
	return (path);
}

void	find_path(t_cmd *cmd, t_prompt *prompt)
{
	int		i;
	char	**paths;
	int		j;
	
	j = 0;
	i = -1;
	paths = ft_split(get_environments("PATH", prompt), ':');
	if (!paths)
	{
		while(cmd->full_cmd[j])
		{
			if (access(cmd->full_cmd[j], F_OK | X_OK) == 0)
				return ;
			return ;
			j++;
		}
	}
	while (paths[++i])
	{
		cmd->full_path = ft_strjoin(paths[i], "/");
		cmd->full_path = ft_strjoin(cmd->full_path, cmd->full_cmd[0]);
		if (access(cmd->full_path, F_OK | X_OK) == 0)
			return ;
	}
}


