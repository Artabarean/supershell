/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:49:17 by codespace         #+#    #+#             */
/*   Updated: 2026/02/09 16:48:25 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env_array(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export(t_prompt *prompt)
{
	char	**env;
	int		i;

	env = env_to_array(prompt->enviroment);
	sort_env_array(env);
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("declare -x %s\n", env[i]);
		else
			printf("declare -x %s\n", env[i]);
		free(env[i]);
		i++;
	}
	free(env);
}

void	export_builtin(t_prompt *prompt, t_cmd *cmd)
{
	int	i;

	if (!cmd->full_cmd[1])
	{
		print_export(prompt);
		prompt->exit_status = 0;
		return ;
	}
	i = 1;
	while (cmd->full_cmd[i])
	{
		if (!is_valid_identifier(cmd->full_cmd[i]))
		{
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
			prompt->exit_status = 1;
		}
		else
			env_add_or_update(prompt, cmd->full_cmd[i]);
		i++;
	}
}
