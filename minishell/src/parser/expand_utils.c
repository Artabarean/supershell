/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:07:02 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/29 10:14:41 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_dollar(char *result)
{
	char	*tmp;
	char	*value;

	value = ft_strdup("$");
	tmp = result;
	result = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	return (result);
}

char	*extract_e_status(char *result)
{
	char	*tmp;
	char	*value;

	value = ft_itoa(g_exit_status);
	tmp = result;
	result = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	return (result);
}

char	*extract_pid(char *result)
{
	char	*tmp;
	char	*value;

	value = ft_itoa(getpid());
	tmp = result;
	result = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	return (result);
}

char	*extract_str(char *result, char *str, int *i, t_env *env)
{
	char	*tmp;
	char	*value;
	char	*var;
	int		start;

	start = *i;
	if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return (result);
	}
	while (str[*i] && is_valid_var_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = expand_var(var, env);
	free(var);
	if (value)
	{
		tmp = result;
		result = ft_strjoin(tmp, value);
		free(tmp);
		free(value);
	}
	return (result);
}

char	*extract_char(char *result, char value)
{
	char	c[2];
	char	*tmp;

	tmp = result;
	c[0] = value;
	c[1] = '\0';
	result = ft_strjoin(tmp, c);
	free(tmp);
	return (result);
}
