/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:36 by medel-ca          #+#    #+#             */
/*   Updated: 2025/10/30 19:59:36 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*expand_var(char *str, t_env *enviroment)
{
	char	*exp_str;

	if (!str || !*str)
		return (ft_strdup(""));
	if (!ft_strncmp(str, "PATH", 4))
		exp_str = ft_strdup(enviroment->path);
	else if (!ft_strncmp(str, "HOME", 4))
		exp_str = ft_strdup(enviroment->home);
	else if (!ft_strncmp(str, "PWD", 3))
		exp_str = ft_strdup(enviroment->pwd);
	else if (!ft_strncmp(str, "OLDPWD", 6))
		exp_str = ft_strdup(enviroment->oldpwd);
	else if (!ft_strncmp(str, "USER", 4))
		exp_str = ft_strdup(enviroment->user);
	else if (!ft_strncmp(str, "SHELL", 5))
		exp_str = ft_strdup(enviroment->shell);
	else if (!ft_strncmp(str, "SHLVL", 5))
		exp_str = ft_strdup(ft_itoa(enviroment->shlvl));
	else if (!ft_strncmp(str, "_", 1))
		exp_str = ft_strdup(enviroment->cmdpath);
	else
		exp_str = ft_strdup("");
	return (exp_str);
}

char	*expand(char **input, t_env *enviroment)
{
	int		len;
	char	*temp;
	char	*var;

	len = 0;
	if (**input == '$')
	{
		(*input)++;
		while (ft_isalnum(**input) || **input == '_')
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
	else
		return (NULL);
}

char	*extract_str_quote(char **input)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*input)[len] && (*input)[len] != '$' && (*input)[len] != '"')
		len++;
	temp = ft_substr(*input, 0, len);
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
