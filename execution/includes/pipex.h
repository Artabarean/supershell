/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:44:12 by alex              #+#    #+#             */
/*   Updated: 2025/10/23 12:04:30 by atabarea         ###   ########.fr       */
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

/* Mandatory functions */
void	error(void);
char	*find_path(char *cmd, char **envp);
int		get_next_line(char **line);
void	execute(char **full_cmd, char *full_path, t_prompt *prompt);
int		pipex(t_prompt *prompt);

/* Bonus functions */
int		open_file(char *argv, int i);
void	usage(void);

#endif
