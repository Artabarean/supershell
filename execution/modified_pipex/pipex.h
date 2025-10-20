/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:51:34 by alex              #+#    #+#             */
/*   Updated: 2025/10/20 12:46:53 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	exec(char *cmd, char **env, int term_fd);
void	child(char **av, char **envp, int *fd, int term_fd);
void	second_child(char **argv, int *p_fd, char **envp, int term_fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
void	error_comm(char *comm, char **freeable, int term_fd);
void	error_commfr(char *comm, char **freeable, int term_fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	error(char *comm, int *p_fd);
void	freer(char **s_cmd);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*get_path(char *cmd, char **envp, char **freecom, int term_fd);
char	*get_environments(char *name, char **env);
int		open_file(char *file, int create_or_open, int *p_fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	handle_exit(void);
size_t	ft_wrdcnt(char const *s, char c);
void	error_filen(char *s, int *p_fd);
void	error_cl(int *fd);
void	fd_closer(int *p_fd);
void	pid_check(int pid);
void	error_cmd(char *cmd, char **freecom, int term_fd);
int		pipex(int argc, char *argv[], char **envp);

#endif