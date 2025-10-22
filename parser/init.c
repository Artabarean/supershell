#include "parser.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*c;

	c = malloc(sizeof(t_cmd));
	if (c)
		return (NULL);
	c->full_cmd = malloc(sizeof(char *) * MAX_TOKENS);
	c->full_path = NULL;
	c->infile = 0;
	c->outfile = 0;
	c->append = 0;
	c->next = NULL;
}

void	init_tkns(t_prompt *prompt)
{
	prompt->tkns = malloc(sizeof(char*) * MAX_TOKENS);
    if (!prompt->tkns)
        //free_all ; ?
		exit (EXIT_FAILURE);
}

void	init_env(t_prompt *prompt, char **env)
{
	t_env	*e;	

	prompt->enviroment = malloc(sizeof(t_env));
	if (!prompt->enviroment)
		return ;
	e = prompt->enviroment;
	e->path = NULL;
	e->home = NULL;
	e->pwd = NULL;
	e->oldpwd = NULL;
	e->user = NULL;
	e->shell = NULL;
	e->shlvl = 0;
	e->cmdpath = NULL;
	parse_env(e, env);
}

void	init_prompt(t_prompt *prompt, char **envp)
{
	prompt->cmds = NULL;
	prompt->imput = NULL;
	prompt->tkns = NULL;
	prompt->pid = 0;
	init_env(prompt, envp);
}
