#ifndef PARSER_H
# define PARSER_H
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include "libft.h"
# include <limits.h>
# include <sys/wait.h>

//Macros para printf
# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\033[0;34m"
# define BOLD    "\033[1m"
# define RESET   "\033[0m"

# define MAX_TOKENS	100

// Estructura para cada comando
typedef struct s_cmd
{
	char			**full_cmd;	//cmd, argumentos, opciones...
	char			*full_path;
	char			*infile;
	char 			*outfile;
	int 			append;
	struct s_cmd	*next;
}			t_cmd;

// Enviroment
typedef struct s_env
{
	char	*path;
	char	*home;
	char	*pwd;
	char	*oldpwd;
	char	*user;
	char	*shell;
	int		shlvl;
	char	*cmdpath;
}				t_env;

// Estructura general
typedef struct s_prompt
{
	t_cmd	*cmds;	//lista de nodos de la otra estructura con los comandos ya separados
	char	*imput;
	char	**tkns;
	t_env	*enviroment;
	pid_t	pid ;
}			t_prompt;

//Enviroment
void	parse_env(t_env *e, char **env);
//Init
void	init_tkns(t_prompt *prompt);
void	init_env(t_prompt *prompt, char **env);
void	init_prompt(t_prompt *prompt, char **envp);
t_cmd	*new_cmd(void);
//Lexer utils
char	*expand_var(char *str,t_env *enviroment);
char	*expand(char **imput, t_env *enviroment);
char	*extract_str_quote(char **imput);
char	*expand_or_empty(char **imput, t_env *env);
char	*handle_quote_content(char **imput, t_env *env);
//lexer
void	lexer(t_prompt *prompt);
char	*extract_word(char **imput);
char	*extract_and_expand(char **imput, t_env *env);
char	*extract_str(char **imput);
//Utils
int		ft_chrcmpr( char prompt, char sym);
char	*ft_strjoin_free(char *s1, char *s2);
void	add_cmd_back(t_cmd **lst, t_cmd *new);

//parser
void	parser(t_prompt *prompt);

#endif