/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:50 by medel-ca          #+#    #+#             */
/*   Updated: 2026/01/27 15:07:50 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg_to_cmd(char *arg, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->full_cmd[i])
		i++;
	cmd->full_cmd[i] = ft_strdup(arg);
	cmd->full_cmd[i + 1] = NULL;
}

bool	create_file(t_toktype type, char *filename, t_cmd *curr)
{
	if (!filename || !curr)
		return (false);
	if (!is_redirection_type(type))
		return (false);
	add_file(curr, filename, type);
	return (true);
}

void	add_file(t_cmd *cmd, char *filename, t_toktype type)
{
	t_redir	*curr;
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->file = filename;
	new->type = type;
	new->next = NULL;
	if (!cmd->redir)
	{
		cmd->redir = new;
		return ;
	}
	curr = cmd->redir;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}
