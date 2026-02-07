/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_find_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:36:05 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/06 18:02:06 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int find_path2(t_cmd *cmd, t_prompt *prompt)
// {
//     char    **paths;
//     char    *tmp;
//     int     i;

//     if(cmd->full_cmd[0][0] == '\0')
// 		return (0);
// 	if (ft_strchr(cmd->full_cmd[0], '/'))
//     {
//         cmd->full_path = ft_strdup(cmd->full_cmd[0]);
//         return (cmd->full_path != NULL);
//     }
//     paths = ft_split(get_environments("PATH", prompt), ':');
//     if (!paths)
//         return (0);
//     i = 0;
//     while (paths[i])
//     {
//         tmp = joiner(paths[i], cmd);
//         if (tmp && access(tmp, F_OK) == 0)
//             return (cmd->full_path = tmp, free_doble_ptr(paths), 1);
//         free(tmp);
//         i++;
//     }
//     free_doble_ptr(paths);
//     return (0);
// }

// void	errormsg(t_prompt *prompt, char *full_cmd, int j, int error)
// {
//     char    *messg;

//     messg = ft_strjoin("minishell: ", full_cmd);
// 	if (error == 1)
// 		prompt->error_msg[j] = ft_strjoin(messg, ": command not found\n");
// 	else if ( error == 2)
// 		prompt->error_msg[j] = ft_strjoin(messg, ": No such file or directory\n");
// 	else if (error == 3)
// 		prompt->error_msg[j] = ft_strjoin(messg, ": Is a directory\n");
// 	else if (error == 4)
// 		prompt->error_msg[j] = ft_strjoin(messg, ": Permission denied\n");
// 	ft_putstr_fd(prompt->error_msg[j], 2);
//     free(prompt->error_msg[j]);
// 	free(messg);
// }

// int	resolve_and_check(t_cmd *cmd, t_prompt *prompt, int index)
// {
// 	struct stat st;
//     if (!find_path2(cmd, prompt))
//     {
//         errormsg(prompt, cmd->full_cmd[0], index, 1);
//         return (prompt->exit_status = 127, 0);
//     }
//     if (stat(cmd->full_path, &st) == -1)
//     {
// 		errormsg(prompt, cmd->full_cmd[0], index, 2);
//         return (prompt->exit_status = 127, 0);
//     }
//     if (S_ISDIR(st.st_mode))
//     {
//         errormsg(prompt, cmd->full_cmd[0], index, 3);
//         return (prompt->exit_status = 126, 0);
//     }
//     if (access(cmd->full_path, X_OK) != 0)
//     {
//         errormsg(prompt, cmd->full_cmd[0], index, 4);
//         return (prompt->exit_status = 126, 0);
//     }
//     return (1);
// }

// void    handle_prechildprocess(t_cmd *cmd, t_prompt *prompt, int i)
// {
//     forker(prompt, i);
// 	if (prompt->pid[i] == 0)
// 	{
// 		set_signal(SIG_CHILD);
// 		child_process(cmd, prompt, i, prompt->n_cmds);
// 	}
// 	else if (is_builtin(cmd) == 0)
// 		find_path(cmd, prompt);
// 	check_error(cmd, prompt, i);
// 	cmd = cmd->next;
// }
