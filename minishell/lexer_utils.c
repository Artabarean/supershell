/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:36 by medel-ca          #+#    #+#             */
/*   Updated: 2025/12/02 16:13:22 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*expand_var(char *str, t_env *enviroment)
{
	char	*exp_str;

	if (!str || !*str)
		return (ft_strdup(""));
	while (enviroment->next)
	{
		if (!ft_strncmp(str, enviroment->keyword,
				ft_strlen(enviroment->keyword)))
		{
			exp_str = ft_strdup(enviroment->value);
			break ;
		}
		if (enviroment->next == NULL)
			return (NULL);
		else
			enviroment = enviroment->next;
	}
	return (exp_str);
}

char	*expand(char **input, t_env *enviroment)
{
	int		len;
	char	*temp;
	char	*var;

	len = 0;
	(*input)++;
	if (**input == '"' || **input == ' ' || **input == '\'')
		return (ft_strdup("$"));
	if (**input == '$')
	{
		(*input)++;
		return (expand_var("SYSTEMD_EXEC_PID", enviroment));
	}
	while (ft_isalnum(**input) || **input == '_' || **input == '$')
	{
		(*input)++;
		len++;
	}
	temp = ft_substr(*input - len, 0, len);
	var = expand_var(temp, enviroment);
	free(temp);
	if (!var)
		return (NULL);
	return (var);
}

char	*extract_str_quote(char **input)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*input)[len] && (*input)[len] != '$' && (*input)[len] != '"')
		len++;
	while ((*input)[len] && (*input)[len] != ' ' )
		len++;
	temp = ft_substr_quotes(*input, 0, len);
	if (!temp)
		return (NULL);
	(*input) += len;
	return (temp);
}

char	*expand_or_empty(char **input, t_env *env)
{
	char	*var;

	var = expand(input, env);
	if (!var)
		var = ft_strdup("");
	return (var);
}

char	*handle_quote_content(char **input, t_env *env)
{
	char	*buffer;
	char	*temp;
	char	*var;

	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	while (**input && **input != '"')
	{
		if (**input == '$')
			var = expand_or_empty(input, env);
		else
			var = extract_str_quote(input);
		if (!var)
			return (free(buffer), NULL);
		temp = buffer;
		buffer = ft_strjoin_free(buffer, var);
	}
	return (buffer);
}
