/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:29 by medel-ca          #+#    #+#             */
/*   Updated: 2026/02/06 12:14:02 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_user_input(t_prompt *prompt)
{
	char	*user;
	char	*temp;

	if (!prompt)
		exit(EXIT_FAILURE);
	temp = get_user(prompt);
	user = ft_strjoin(temp, "@minishell: ");
	set_signal(SIG_PROMPT);
	if (g_sign)
		prompt->exit_status = g_sign;
	prompt->input = readline(user);
	if (prompt->input && not_only_spaces(prompt->input))
	{
		add_history(prompt->input);
		prompt->tkns_nbr = count_input(prompt->input);
		init_tkns(prompt);
	}
	free(user);
	free(temp);
}

static int	is_valid_input(char *input)
{
	int	end;

	input = ft_strtrim(input, " \t\r\n\v");
	end = 0;
	if (!input[0] || input[0] == '|')
	{
		if (input[0] == '|')
			syntax_error(&input[end]);
		free(input);
		return (0);
	}
	end = ft_strlen(input) - 1;
	if (input[end] == '|' || input[end] == '<' || input[end] == '>')
	{
		if (input[end] == '|')
			syntax_error(&input[end]);
		else if ((input[end] == '<' || input[end] == '>'))
			syntax_error(&input[end]);
		free(input);
		return (0);
	}
	free (input);
	return (1);
}

static int	closed_quotes(char *input)
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
