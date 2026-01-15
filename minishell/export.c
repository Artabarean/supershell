/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:49:17 by codespace         #+#    #+#             */
/*   Updated: 2026/01/12 16:24:01 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	sort_env_array(char **env)
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

void	print_export(t_prompt *prompt)
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

	printf("hola\n");
	if (!cmd->full_cmd[1])
	{
		print_export(prompt);
		prompt->exit_stat = 0;
		return ;
	}
	i = 1;
	while (cmd->full_cmd[i])
	{
		if (!is_valid_identifier(cmd->full_cmd[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				cmd->full_cmd[i]);
			prompt->exit_stat = 1;
		}
		else
			env_add_or_update(prompt, cmd->full_cmd[i]);
		i++;
	}
}
