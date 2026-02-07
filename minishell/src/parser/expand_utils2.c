/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:04:51 by medel-ca          #+#    #+#             */
/*   Updated: 2026/02/07 17:42:36 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static void	delate_tkn(t_prompt *prompt)
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
		prompt->tkns[i] = expand(prompt->tkns[i], prompt);
		if (prompt->tkns[i][0] == '\0' && prompt->quotes[i] == Q_NONE)
			delate_tkn(prompt);
		else
			i++;
	}
}
