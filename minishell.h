/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:04:20 by atabarea          #+#    #+#             */
/*   Updated: 2025/10/20 12:59:35 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_list
{
	char	*dividedcmd;
	t_list	*next;
}		t_list;


typedef struct s_prompt
{
	t_list	*cmds;
	char	**environment;
	pid_t	pid;
	
}		s_prompt;

typedef struct s_cmd
{
	char	**full_cmd;
	char	*full_path;
	char	*infile;
	char	*outfile;
	s_cmd 	*next;
}		s_cmd;

#endif