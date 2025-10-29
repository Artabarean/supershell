/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:44:12 by alex              #+#    #+#             */
/*   Updated: 2025/10/29 12:26:15 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../../parser/parser.h"

void	error(void);
int		get_next_line(char **line);
void	execute(char **full_cmd, char *full_path, t_prompt prompt);
int		pipex(t_prompt prompt);
int		open_file(char *argv, int i);
void    check_status(int status);
void    file_opener(t_prompt prompt, int fileout, int filein);
void    childprocess_(t_cmd *curr_nde, int filein, int fileout, t_prompt prompt);
int		pid_stat(t_cmd *curr_nde ,t_prompt prompt, int status, int last_status);

#endif
