/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:14:33 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/27 15:07:26 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_for_heredoc(char *str, t_env *env)
{
	char	*keyword;

	keyword = NULL;
	if (!str || !*str)
		return (ft_strdup(""));
	while (env)
	{
		keyword = ft_strjoin("$", env->keyword);
		if (!ft_strcmp(str, keyword))
			return (free(keyword), ft_strdup(env->value));
		free(keyword);
		env = env->next;
	}
	return (str);
}

int	handle_heredoc(t_prompt *prompt, t_cmd *cmd, int *fin)
{
	if (cmd->redir && cmd->redir->type == T_HEREDOC)
	{
		process_heredocs(cmd, prompt->enviroment);
		*fin = get_last_heredoc(cmd->tmp_doc);
		if (*fin == -1)
		{
			closepfds(prompt->n_cmds, prompt);
			return (1);
		}
	}
	return (0);
}

char	**count_heredoc(t_redir *redir)
{
	t_redir *copy;
	int		count;
	char	**sizer;

	count = 0;
	copy = redir;
	while(copy)
	{
		if (copy->type == T_HEREDOC)
			count++;
		copy = copy->next;
	}
	sizer = malloc(sizeof(char *) * (count + 1));
	sizer[count] = NULL;
	return (sizer);
}
