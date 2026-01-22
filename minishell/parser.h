/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:00:00 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/20 10:17:59 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
#include <sys/stat.h>
# include "../execution/libft/libft.h"
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
} t_signal_context;

extern volatile sig_atomic_t g_exit_status;

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

// Estructura para cada comando
typedef struct s_cmd
{
	char			**full_cmd;
	char			*full_path;
	char			**tmp_doc;
	int				max_tkns;
	t_redir			*redir;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_env
{
	char			*keyword;
	char			*value;
	struct s_env	*next;
	char			**envp;
}			t_env;

// Estructura general
typedef struct s_prompt
{
	t_cmd		*cmds;
	char		*input;
	char		**tkns;
	int			tkns_nbr;
	t_toktype	*types;
	t_quote		*quotes;
	char		**error_msg;
	int			(*pfd)[2];
	t_env		*enviroment;
	pid_t		*pid;
	int			pip_exec;
}			t_prompt;

//Enviroment
void	fill_env(char *env, t_env *e);
t_env	*new_env(void);
void	init_env(t_prompt *prompt, char **env);
char	*get_user(t_prompt *prompt);
char	**env_to_envp(t_env *env);

//Init
void	init_tkns(t_prompt *prompt);
void	init_prompt(t_prompt *prompt, char **envp);
t_cmd	*create_cmd(t_prompt *prompt);
int		count_input(char *input);

//Lexer utils
void	extract_sym(char **ptr, t_prompt *prompt, int index);

//Lexer utils 2
char	*extract_single_quote(char **input);
char	*extract_double_quote(char **input);

//lexer
int		lexer(t_prompt *prompt);
char	*extract_token(char **input, t_prompt *prompt, int i);
char	*extract_word_part(char **input);
int		is_separator(char c);
void	extract_sym(char **ptr, t_prompt *prompt, int index);

//Utils
int		ft_chrcmpr( char prompt, char sym);
char	*ft_strjoin_free(char *s1, char *s2);
void	add_cmd_back(t_cmd **lst, t_cmd *new);
void	syntax_error(char *token);
int		is_redirection_type(t_toktype type);

//parser utils
void	add_arg_to_cmd(char *arg, t_cmd *cmd);
bool	create_file(t_toktype type, char *filename, t_cmd *curr);
void	add_file(t_cmd *cmd, char *filename, t_toktype type);

//parser
bool	parser(t_prompt *prompt, t_cmd *curr);
bool	init_parser(t_prompt *prompt);

//expand
void	expand_tkn(t_prompt *prompt);
char	*expand(char *str, t_env *env);
int		is_valid_var_char(char c);
char	*expand_var(char *str, t_env *enviroment);

//expand utils
char	*extract_dollar(char *result);
char	*extract_e_status(char *result);
char	*extract_str(char *result, char *str, int *i, t_env *env);
char	*extract_char(char *result, char value);
char	*expand_dollar(char *res, char *str, int *i, t_env *env);

//clean
void	free_all(t_prompt *prompt);
void	free_cmds(t_cmd **lst);
void	free_doble_ptr(char **ptr);
void	free_env(t_env *e);
void	free_input(t_prompt *prompt);

//Input
void	get_user_input(t_prompt *prompt);
int		is_valid_input(char *input);
int		correct_input(char *input);
int		not_only_spaces(char *input);

//Valid comands
int		cmds_valids(t_prompt prompt);

//Signals
void	set_signal(int status);
void	close_heredoc(int signal);
void	reset_shell(int signal);

//Debugging
void	debug(t_prompt prompt);

//Execution
void	error(char *s);
void	here_doc(t_cmd *cmds);
int		get_next_line(char **line);
void	execute(char **full_cmd, char *full_path, t_prompt *prompt);
void	pipex(t_prompt prompt);
int		open_file(char *argv, int i);
void	check_status(int last_status);
void	file_opener(t_prompt *prompt, t_cmd *cmd, int *fileout, int *filein);
void	childprocess_(t_cmd *curr_nde, t_prompt *prompt);
int		pid_stat(t_cmd *curr_nde, t_prompt *prompt, int last_status);
int		execute_(t_cmd *cmd, t_prompt *prompt);
void	executer(t_prompt *prompt);
void	pfd_alloc(t_prompt *prompt, int n_cmds);
void	find_outfile(t_cmd *cmd, int *fileout);
void	find_infile(t_cmd *cmd, int *filein);
void	check_command(t_cmd *cmd, t_prompt *prompt);

void	child_process1(t_cmd *curr_node, int fin, int fout, t_prompt *prompt);
void	child_processmid(t_cmd *curr_node, t_prompt *prompt, int i);
void	child_processend(t_cmd *curr_node, int fout, t_prompt *prompt, int i);
int		pipecount(t_prompt prompt);
int		find_path(t_cmd *cmd, t_prompt *prompt, int i);
void	closepfds(int n_cmds, t_prompt *prompt);
void	selectprocess(t_prompt *prompt, t_cmd *cmd, int i, int *fin, int *fout);
void	forker(t_prompt *prompt, int i);
void	free_double(char *str1, char *str2);
int		find_path_no_print(t_cmd *cmd, t_prompt *prompt);
void	create_pipes(t_prompt *prompt, int n_cmds);
void	check_error(t_prompt *prompt, int i);

//Here_doc
int		process_heredocs(t_cmd *cmd, t_env *env);
int		count_strs(char	**str);
int		get_last_heredoc(char **tmp_doc);
void	cleanup_heredoc_files(t_cmd *cmds);
void	here_doc_check(char **here_doc, int *fin);
char	**count_heredoc(t_redir *redir);

//Built-ins
int		is_builtin(t_cmd *cmd);
int		single_builtin(int n_cmds, t_cmd *cmd, t_prompt *prompt, int filein, int fileout);
int		builtin_no_in_out(int n_cmds, t_cmd *cmd, t_prompt *prompt);
void	run_builtin_son(t_cmd *cmd, int fin, int fout);
int		run_builtin_child(t_cmd *cmd, t_prompt *prompt);
int		checkfather_builtin(t_cmd *cmd);
void	exit_builtin(t_cmd *cmd, t_prompt *prompt);
int		builtin_unset(char **args, t_prompt *prompt);
int		is_valid_identifier(char *s);
char	*get_env_value(t_env *env, const char *name);
void	printnofile(t_prompt *prompt, char *full_cmd, int j);
t_env	*env_find(t_env *env, char *key);
void	env_add_or_update(t_prompt *prompt, char *arg);
int		env_size(t_env *env);
char	**env_to_array(t_env *env);
int		do_path(t_env *env, char *path, char *selection);
int		env(t_prompt *prompt, char **args);
int		pwd(void);
void	echo(char **full_cmd, t_env *env);
int		cd(char **args, t_prompt *prompt);
void	export_builtin(t_prompt *prompt, t_cmd *cmd);

#endif
