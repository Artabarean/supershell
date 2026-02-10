/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:28:26 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/10 16:34:49 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(char *res, char *str, int *i, t_prompt *prompt)
{
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (extract_e_status(res, prompt->exit_status));
	}
	if (!str[*i] || !ft_isalnum(str[*i]))
		return (extract_dollar(res));
	return (extract_str(res, str, i, prompt->enviroment));
}

char	*expand(char *str, t_prompt *prompt)
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
		result = expand_dollar(result, str, &i, prompt);
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
