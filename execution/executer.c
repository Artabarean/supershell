/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:07 by alex              #+#    #+#             */
/*   Updated: 2025/10/23 12:44:29 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void    executer(t_prompt prompt)
{
	if (prompt.cmds->infile && prompt.cmds->outfile)
		pipex(prompt);
	else
		execute(prompt.cmds->full_cmd, prompt.cmds->full_path, prompt);
}
