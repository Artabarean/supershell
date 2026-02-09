/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:00:00 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/09 17:16:30 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../inc/libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>

//Macros para printf
# define RED	 "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE	"\033[0;34m"
# define BOLD	"\033[1m"
# define RESET   "\033[0m"

//Valores para controlar las señales
typedef enum e_signal_context
{
	SIG_PROMPT,
	SIG_CHILD,
	SIG_WAIT,
	SIG_HEREDOC
}	t_signal_context;

extern volatile sig_atomic_t g_sign;

typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote;

typedef enum e_toktype
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_toktype;

typedef struct s_redir
{
	t_toktype		type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**full_cmd;
	char			*full_path;
	char			**tmp_doc;
	t_redir			*redir;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_env
{
	char			*keyword;
	char			*value;
	struct s_env	*next;
}			t_env;

// Estructura general
typedef struct s_prompt
{
	t_cmd		*cmds;
	char		*input;
	int			n_cmds;
	char		**tkns;
	int			tkns_nbr;
	int			iter;
	t_toktype	*types;
	t_quote		*quotes;
	char		**error_msg;
	int			(*pfd)[2];
	t_env		*enviroment;
	pid_t		*pid;
	int			pip_exec;
	int			exit_status;
}			t_prompt;

//CORE
char	*get_user(t_prompt *prompt);
void	get_user_input(t_prompt *prompt);
void	init_tkns(t_prompt *prompt);
void	init_prompt(t_prompt *prompt, char **envp);
t_cmd	*create_cmd(t_prompt *prompt);

//LEXER
int		lexer(t_prompt *prompt);
char	*extract_single_quote(char **input);
char	*extract_double_quote(char **input);
void	extract_sym(char **ptr, t_prompt *prompt, int index);

//EXPANSIONES
char	*expand(char *str, t_prompt *prompt);
char	*expand_dollar(char *res, char *str, int *i, t_prompt *prompt);
void	expand_tkn(t_prompt *prompt);
char	*expand_var(char *str, t_env *enviroment);
char	*extract_dollar(char *result);
char	*extract_e_status(char *result, int status);
char	*extract_pid(char *result);
char	*extract_str(char *result, char *str, int *i, t_env *env);
char	*extract_char(char *result, char value);
char	**ft_split_spc(const char *s);

//PARSER
bool	init_parser(t_prompt *prompt);
void	add_arg_to_cmd(char *arg, t_quote quote, t_cmd *cmd);
bool	create_file(t_toktype type, char *filename, t_cmd *curr);
void	add_file(t_cmd *cmd, char *filename, t_toktype type);

//EJECUCIÓN
void	executer(t_prompt *prompt);
int		execute_(t_cmd *cmd, t_prompt *prompt);
void	execute(char **full_cmd, char *full_path, t_prompt *prompt);
void	pipex(t_prompt *prompt);
int		check_paths(t_cmd *cmd, char **paths);
void	child_process(t_cmd *cmd, t_prompt *prompt, int i, int n_cmds);
void	childprocess_(t_cmd *curr_nde, t_prompt *prompt);
void	child_process1(t_cmd *curr_node, int fin, int fout, t_prompt *prompt);
void	child_processpfd(t_cmd *cmd, int fin, int i, t_prompt *prompt);
void	child_processmid(t_cmd *curr_node, t_prompt *prompt, int i);
void	child_processend(t_cmd *curr_node, int fout, t_prompt *prompt, int i);
void	selectprocess(t_prompt *prompt, t_cmd *cmd, int *fin, int *fout);

//BUILT-INS
void	exit_builtin(t_cmd *cmd, t_prompt *prompt);
int		builtin_unset(char **args, t_prompt *prompt);
int		cd(char **args, t_prompt *prompt);
int		pwd(void);
void	echo(char **full_cmd);
void	export_builtin(t_prompt *prompt, t_cmd *cmd);

//ENVIRONMENT
int		env(t_prompt *prompt, char **args);
void	init_env(t_prompt *prompt, char **env);
void	free_env(t_env *env);
char	*get_env_value(t_env *env, const char *name);
char	*get_environments(char *name, t_prompt *prompt);
void	env_add_or_update(t_prompt *prompt, char *arg);
char	**env_to_array(t_env *env);
int		ispath(t_prompt *prompt);
int		do_path(t_env *env, char *path, char *selection);

//CLEAN
void	free_all(t_prompt *prompt);
void	free_doble_ptr(char **ptr);
void	free_env(t_env *e);
void	free_input(t_prompt *prompt);

//SIGNALS
void	set_signal(int status);

//UTILS
int		cmd_isdir(t_cmd *cmd, char *full_cmd);
char	*joiner(char *paths, t_cmd *cmd);
void	forker(t_prompt *prompt, int i);
void	pid_util(int *wstatus, t_prompt *prompt, int *last_status, int i);

//Core
int		count_input(char *input);
int		correct_input(char *input);
int		not_only_spaces(char *input);

//Lexer
int		is_separator(char c);

//Expansion
int		is_valid_var_char(char c);

//Execution
int		error(char *s);
void	error_in_child(char *s);
void	error_no_exit(char *s);
void	check_error(t_cmd *cmd, t_prompt *prompt, int i);

//Redirections
int		redirin(t_redir *redir);
int		redirout(t_redir *redir);
void	set_fd(int *fd, int value);
int		open_file(char *name, int i);
void	file_opener(t_prompt *prompt, t_cmd *cmd, int *fileout, int *filein);
void	find_outfile_child(t_redir *redir, int *fileout);
void	find_infile_child(t_redir *redir, int *filein);
void	find_heredoc_child(t_cmd *cmd, int *filein);
int		find_outfile(t_redir *redir, int *fileout);
int		find_infile(t_redir *redir, int *filein);
int		find_heredoc(t_cmd *cmd, int *filein);

void	check_status(t_prompt prompt, int last_status);
int		pid_stat(t_cmd *curr_nde, t_prompt *prompt, int last_status);
void	pfd_alloc(t_prompt *prompt, int n_cmds);
void	check_command(t_cmd *cmd, t_prompt *prompt, int *fout, int *fin);
void	check_com(t_cmd *cmd, t_prompt *prompt);
int		pipecount(t_prompt prompt);
int		find_path(t_cmd *cmd, t_prompt *prompt, int i);
int		find_path_no_print(t_cmd *cmd, t_prompt *prompt);
//int		resolve_and_check(t_cmd *cmd, t_prompt *prompt, int index);
//void    handle_prechildprocess(t_cmd *cmd, t_prompt *prompt, int i);
//int 	find_path2(t_cmd *cmd, t_prompt *prompt);
void	closepfds(int n_cmds, t_prompt *prompt);
void	create_pipes(t_prompt *prompt, int n_cmds);

//Here_doc
int		process_heredocs(t_cmd *copycmd, t_prompt *prompt);
int		count_strs(char	**str);
int		eof_warning_msg(char *line, char *limiter);
char	*expand_for_heredoc(char *str, t_prompt *prompt);
int		handle_heredoc(t_prompt *prompt, t_cmd *cmd);
int		get_last_heredoc(char **tmp_doc);
void	cleanup_heredoc_files(t_cmd *cmds);
int		heredoc_sig_check(void);
char	**count_heredoc(t_redir *redir);
void	fd_failed_hd(char *filename);
void	createfile(t_cmd *cmd, int *fd);
void	closehfd(int *fd);
int		*count_hfds(t_cmd *cmd);
void	set_tempdoc(t_cmd *cmd);
int		see_if_heredoc(t_cmd *cmd, t_prompt *prompt, int is_heredoc);
int		heredoc_open(t_cmd *copycmd, int i, int j);
void	set_hdoc_child(t_cmd *cmd, int *fd, t_prompt *prompt);
int		heredoc_child(t_cmd *cmd, int *fd, t_prompt *prompt);

//Built-ins
int		handle_in(t_redir *redir, int *fin);
int		handle_out(t_redir *redir, int *fout);
int		handle_hdoc(t_cmd *cmd, int *fin);
int		too_many_args(char **args);
char	*printpath(t_prompt *prompt);
void	update_node(t_env *node, t_prompt *prompt, char *key, char *value);
int		is_lone_builtin(t_cmd *cmd, t_prompt *prompt, int fin, int fout);
int		builtin_no_in_out(int n_cmds, t_cmd *cmd, t_prompt *prompt);
void	run_builtin_son(t_cmd *cmd, int *fin, int *fout);
int		is_builtin(t_cmd *cmd);
int		run_builtin_child(t_cmd *cmd, t_prompt *prompt);
int		checkfather_builtin(t_cmd *cmd);
void	is_parent(t_cmd *curr_nde, int *wstatus, int *last_status);
int		is_valid_identifier(char *s);

//Other utils
int		ft_chrcmpr( char prompt, char sym);
char	*ft_strjoin_free(char *s1, char *s2);
void	add_cmd_back(t_cmd **lst, t_cmd *new);
void	syntax_error(char *token);
//void	errormsg(t_prompt *prompt, char *full_cmd, int j, int error);
int		is_redirection_type(t_toktype type);

//Debugging
void	debug(t_prompt prompt);
void	print_cmds(t_cmd *cmds);

#endif
