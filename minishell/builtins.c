/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:58:47 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/17 10:59:41 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int is_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
        return (0);
    if (!strcmp(cmd->full_cmd[0], "echo"))
        return (1);
    if (!strcmp(cmd->full_cmd[0], "pwd"))
        return (1);
    if (!strcmp(cmd->full_cmd[0], "cd"))
        return (1);
    if (!strcmp(cmd->full_cmd[0], "export"))
        return (1);
    if (!strcmp(cmd->full_cmd[0], "unset"))
        return (1);
    if (!strcmp(cmd->full_cmd[0], "env"))
        return (1);
    if (!strcmp(cmd->full_cmd[0], "exit"))
        return (1);
    return (0);
}

void run_builtin_child(t_cmd *cmd, t_prompt *prompt)
{
    if (!strcmp(cmd->full_cmd[0], "echo"))
        echo(cmd->full_cmd);
    else if (!strcmp(cmd->full_cmd[0], "pwd"))
        pwd();
    // else if (!strcmp(cmd->full_cmd[0], "env"))
    //     env(prompt, cmd->full_cmd);
    // else if (!strcmp(cmd->full_cmd[0], "export"))
    //     export(cmd->full_cmd);
    // else if (!strcmp(cmd->full_cmd[0], "unset"))
    //     unset(cmd->full_cmd);
    // else if (!strcmp(cmd->full_cmd[0], "cd"))
    // 	cd(cmd->full_cmd, prompt);
    // else if (!strcmp(cmd->full_cmd[0], "exit"))
    //     exit_builtin(cmd);
}
