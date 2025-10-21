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
	int				infile;
	int				outfile;
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

void	parse_env(t_env *e, char **env);
void	init_env(t_prompt *prompt, char **env);
void	lexer(t_prompt *prompt);
char	*expand_var(char *str, t_prompt *prompt);
char	*extract_and_expand(t_prompt *prompt, int index);
char	*extract_str(t_prompt *prompt, int index);
int		ft_chrcmpr( char prompt, char sym);
void	init_tkns(char **tkns);
#endif