/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:36:48 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/03 11:51:31 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_node(t_env *node, t_prompt *prompt, char *key, char *value)
{
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->keyword = key;
	node->value = value;
	node->next = prompt->enviroment;
	prompt->enviroment = node;
}
