/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:50 by medel-ca          #+#    #+#             */
/*   Updated: 2026/02/07 17:39:55 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_count(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

void	add_one_arg(t_cmd *cmd, char *arg)
{
	char	**new;
	int		n;
	int		i;

	n = arg_count(cmd->full_cmd);
	new = malloc(sizeof(char *) * (n + 2));
	i = 0;
	if (!new)
		return ;
	while (i < n)
	{
		new[i] = cmd->full_cmd[i];
		i++;
	}
	new[n] = ft_strdup(arg);
	new[n + 1] = NULL;
	free(cmd->full_cmd);
	cmd->full_cmd = new;
}

void	add_arg_to_cmd(char *arg, t_quote quote, t_cmd *cmd)
{
	char	**split;
	int		i;

	if (quote == Q_NONE)
	{
		split = ft_split_spc(arg);
		i = 0;
		while (split && split[i])
			add_one_arg(cmd, split[i++]);
		free_doble_ptr(split);
	}
	else
		add_one_arg(cmd, arg);
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
