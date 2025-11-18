/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:29 by medel-ca          #+#    #+#             */
/*   Updated: 2025/10/30 19:59:30 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_user_input(t_prompt *prompt)
{
	char	*user;
	char	*temp;
	t_env	*env;

	env = prompt->enviroment;
	temp = NULL;
	if (!prompt)
		exit(EXIT_FAILURE);
	while (env && !temp)
	{
		if (ft_strnstr(env->keyword, "USER", 4))
			temp = ft_strdup(env->value);
		env = env->next;
	}
	if (!temp)
		temp = ft_strdup("guest");
	user = ft_strjoin(temp, "@minishell: ");
	set_signal(PROMPT_RESTART, NULL);
	prompt->input = readline(user);
	if (prompt->input && not_only_spaces(prompt->input))
		add_history(prompt->input);
	free(user);
	free(temp);
}

int	is_valid_input(char *input)
{
	int	end;

	input = ft_strtrim(input, " \t\r\n\v");
	if (!input[0] || input[0] == '|')
	{
		if (input[0] == '|')
			perror("Error de sintaxis");
		free(input);
		return (0);
	}
	end = ft_strlen(input) - 1;
	if (input[end] == '|' || input[end] == '<' || input[end] == '>')
	{
		if (input[end] == '|')
			perror("Error de sintaxis");
		else if ((input[end] == '<' || input[end] == '>'))
			perror("Error de redirección");
		free(input);
		return (0);
	}
	free (input);
	return (1);
}

int	closed_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (!input[i])
				return (0);
		}
		if (input[i] == '"')
		{
			i++;
			while (input[i] && input[i] != '"')
				i++;
			if (!input[i])
				return (0);
		}
		i++;
	}
	return (1);
}

int	not_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	correct_input(char *input)
{
	if (input && is_valid_input(input)
		&& not_only_spaces(input) && closed_quotes(input))
		return (1);
	else
		return (0);
}
