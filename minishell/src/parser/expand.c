/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:28:26 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/30 09:44:46 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_dollar(char *res, char *str, int *i, t_env *env)
{
	(*i)++;
	if (!str[*i] || str[*i] == ' ' || str[*i] == '"'
		|| str[*i] == '\'' || str[*i] == '(')
		return (extract_dollar(res));
	if (str[*i] == '?')
	{
		(*i)++;
		return (extract_e_status(res));
	}
	if (str[*i] == '$')
	{
		(*i)++;
		return (extract_pid(res));
	}
	return (extract_str(res, str, i, env));
}

char	*expand(char *str, t_env *env)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '$')
		{
			result = extract_char(result, str[i]);
			i++;
			continue ;
		}
		result = expand_dollar(result, str, &i, env);
	}
	free(str);
	return (result);
}

char	*expand_var(char *str, t_env *enviroment)
{
	if (!str || !*str)
		return (ft_strdup(""));
	while (enviroment)
	{
		if (!ft_strcmp(str, enviroment->keyword))
			return (ft_strdup(enviroment->value));
		enviroment = enviroment->next;
	}
	return (NULL);
}
