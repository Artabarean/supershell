/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:59:50 by medel-ca          #+#    #+#             */
/*   Updated: 2025/12/05 10:02:05 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	new_node(t_cmd *current, int *index, t_prompt *prompt)
{
	current->full_cmd[*index] = NULL;
	current = create_cmd(prompt);
	if (!current)
	{
		free_all(prompt);
		exit(EXIT_FAILURE);
	}
	*index = 0;
}

void	add_arg_to_cmd(char *arg, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < MAX_TOKENS - 1 && cmd->full_cmd[i])
		i++;
	if (i == MAX_TOKENS - 1)
	{
		printf("Demasiados argumentos\n");
		return ;
	}
	cmd->full_cmd[i] = ft_strdup(arg);
	cmd->full_cmd[i + 1] = NULL;
}

int	create_file(char ***tkn, t_cmd *curr)
{
	char	*redir;
	char	*filename;

	if (!tkn || !*tkn || !**tkn)
		return (0);
	redir = **tkn;
	(*tkn)++;
	if (!*tkn || !**tkn)
		return (0);
	filename = **tkn;
	if (!ft_strncmp(redir, ">>", 3))
		add_outfile(curr, filename, 1);
	else if (!ft_strncmp(redir, ">", 2))
		add_outfile(curr, filename, 0);
	else if (!ft_strncmp(redir, "<<", 3))
		add_infile(curr, filename, 1);
	else if (!ft_strncmp(redir, "<", 2))
		add_infile(curr, filename, 0);
	(*tkn)++;
	return (1);
}

void	add_infile(t_cmd *cmd, char *filename, int heredoc)
{
	int	i;

	i = 0;
	if (!cmd || !filename)
		return ;
	if (heredoc)
	{
		while (cmd->heredoc[i])
			i++;
		cmd->heredoc[i] = ft_strdup(filename);
	}
	else
	{
		while (cmd->infile[i])
			i++;
		cmd->infile[i] = ft_strdup(filename);
	}
}

void	add_outfile(t_cmd *cmd, char *filename, int append)
{
	int	i;

	i = 0;
	if (!cmd || !filename)
		return ;
	if (append)
	{
		while (cmd->tmp_doc[i])
			i++;
		cmd->tmp_doc[i] = ft_strdup(filename);
		cmd->append = 1;
	}
	else
	{
		while (cmd->outfile[i])
			i++;
		cmd->outfile[i] = ft_strdup(filename);
	}
}
