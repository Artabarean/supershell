/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:28:26 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/26 14:28:26 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
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

void	delate_tkn(t_prompt *prompt)
{
	int	i;

	if (!prompt || !prompt->tkns)
		return ;
	i = 0;
	while (prompt->tkns[i] && prompt->tkns[i][0] != '\0')
		i++;
	if (!prompt->tkns[i])
		return ;
	free(prompt->tkns[i]);
	while (prompt->tkns[i + 1])
	{
		prompt->tkns[i] = prompt->tkns[i + 1];
		prompt->types[i] = prompt->types[i + 1];
		prompt->quotes[i] = prompt->quotes[i + 1];
		i++;
	}
	prompt->tkns[i] = NULL;
}

void	expand_tkn(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt->tkns[i])
	{
		if (prompt->types[i] != T_WORD)
		{
			i++;
			continue ;
		}
		if (prompt->quotes[i] == Q_SINGLE)
		{
			i++;
			continue ;
		}
		prompt->tkns[i] = expand(prompt->tkns[i], prompt->enviroment);
		if (prompt->tkns[i][0] == '\0' && prompt->quotes[i] == Q_NONE)
			delate_tkn(prompt);
		else
			i++;
	}
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
