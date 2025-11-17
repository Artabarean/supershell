/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:13:23 by medel-ca          #+#    #+#             */
/*   Updated: 2025/11/17 14:10:07 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser.h										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: medel-ca <medel-ca@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/10/30 20:00:00 by medel-ca		  #+#	#+#			 */
/*   Updated: 2025/10/30 20:09:33 by medel-ca		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include "../execution/libft/libft.h"
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

//Macros para printf
# define RED	 "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE	"\033[0;34m"
# define BOLD	"\033[1m"
# define RESET   "\033[0m"

# define MAX_TOKENS	100

//Valores para controlar las señales
# define PROMPT_RESTART 1 // ctrl+C o ctrl+\ esperando prompt
# define CHILD_EXIT 2 // ctrl+C cierra proceso hijo o ctrl+\ cierra con core dumped
# define EXIT 3 // ctrl+D en línea vacía
# define HEREDOC 4 // ctrl+D al leer de heredoc

extern int	g_exit_status;

// Estructura para cada comando
typedef struct s_cmd
{
	char			**full_cmd;	//cmd, argumentos, opciones...
	char			*full_path;
	char			**infile;
	char			**outfile;
	int				append;
	int				heredoc;
	struct s_cmd	*next;
}			t_cmd;

//Enviroment
/* typedef struct s_env
{
	char	*path;
	char	*home;
	char	*pwd;
	char	*oldpwd;
	char	*user;
	char	*shell;
	int		shlvl;
	char	*cmdpath;
	char	**envp;
}				t_env; */

typedef struct s_env
{
	char			*keyword;
	char			*value;
	struct s_env	*next;
	char			**envp
}				t_env;

// Estructura general
typedef struct s_prompt
{
	t_cmd	*cmds;	//lista de nodos de la otra estructura con los comandos ya separados
	char	*input;
	char	**tkns;
	int		(*pfd)[2];
	t_env	*enviroment;
	pid_t	pid ;
}			t_prompt;

//Enviroment
void	fill_env(char *env, t_env *e);
t_env	*new_env(void);
void	init_env(t_prompt *prompt, char **env);

//Init
void	init_tkns(t_prompt *prompt);
void	init_env(t_prompt *prompt, char **env);
void	init_prompt(t_prompt *prompt, char **envp);
t_cmd	*new_cmd(void);
t_cmd	*create_cmd(t_prompt *prompt);

//Lexer utils
char	*expand_var(char *str, t_env *enviroment);
char	*expand(char **input, t_env *enviroment);
char	*extract_str_quote(char **input);
char	*expand_or_empty(char **input, t_env *env);
char	*handle_quote_content(char **input, t_env *env);

//lexer
void	lexer(t_prompt *prompt);
char	*extract_word(char **input);
char	*extract_and_expand(char **input, t_env *env);
char	*extract_str(char **input);

//Utils
int		ft_chrcmpr( char prompt, char sym);
char	*ft_strjoin_free(char *s1, char *s2);
void	add_cmd_back(t_cmd **lst, t_cmd *new);

//parser
void	init_parser(t_prompt *prompt);
void	new_node(t_cmd *current, int *index, t_prompt *prompt);
void	add_arg_to_cmd(char *arg, t_cmd *cmd);
int		create_file(char ***tkn, t_cmd *curr);
void	add_infile(t_cmd *cmd, char *filename, int heredoc);
void	add_outfile(t_cmd *cmd, char *filename, int append);

//clean
void	free_all(t_prompt *prompt);
void	free_lst(t_cmd **lst);
void	del(t_cmd *tmp);
void	free_doble_ptr(char **ptr);
void	free_env(t_env **e);

//Input
void	get_user_input(t_prompt *prompt);
int		is_valid_input(char *input);
int		correct_input(char *input);
int		not_only_spaces(char *input);

//Valid comands
int		cmds_valids(t_prompt prompt);

//Signals
void	set_signal(int status, t_prompt *prompt);
void	close_child(int signal);
void	core_dump(int signal);
void	close_heredoc(int signal);
void	reset_shell(int signal);

//Debugging
void	debug(t_prompt prompt);

//Execution
void	error(char *s);
void	here_doc(t_prompt prompt, char *limiter);
int		get_next_line(char **line);
void	execute(char **full_cmd, char *full_path, t_prompt prompt);
void	pipex(t_prompt prompt);
int		open_file(char *argv, int i);
void	check_status(int status);
void	file_opener(t_prompt prompt, int *fileout, int *filein);
void	childprocess_(t_cmd *curr_nde, int filein, int fileout, t_prompt prompt);
int		pid_stat(t_cmd *curr_nde, t_prompt prompt, int status, int last_status);
void	execute_(t_cmd *cmd, t_prompt prompt);
void	executer(t_prompt prompt);

void	child_process1(t_cmd *curr_node , int fin, int fout, t_prompt *prompt, int i);
void	child_processmid(t_cmd *curr_node , t_prompt *prompt, int i);
void	child_processend(t_cmd *curr_node , int fout, t_prompt *prompt, int i);
int		pipecount(t_prompt prompt);
void	find_path(t_cmd *cmd, t_prompt *prompt);
void	closepfds(int n_cmds, t_prompt prompt);
void	selectprocess(t_prompt *prompt, t_cmd *cmd, int i, int fin, int fout);


//Built-ins
int		is_builtin(t_cmd *cmd);
void 	run_builtin_child(t_cmd *cmd, t_prompt *prompt);
int		pwd(void);
int		echo(char **full_cmd);
// int		export(t_prompt prompt);

#endif
