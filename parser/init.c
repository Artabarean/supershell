#include "parser.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*c;

	c = ft_calloc(1, sizeof(t_cmd));
	if (!c)
		return (NULL);
	c->full_cmd = ft_calloc(MAX_TOKENS, sizeof(char *));
	if (!c->full_cmd)
		return (free(c), NULL);
	c->infile = ft_calloc(MAX_TOKENS, sizeof(char *));
	if (!c->infile)
		return (free(c->full_cmd), free(c), NULL);
	c->outfile = ft_calloc(MAX_TOKENS, sizeof(char *));
	if (!c->outfile)
		return (free(c->infile), free(c->full_cmd), free(c), NULL);
	c->full_path = NULL;
	c->append = 0;
	c->heredoc = 0;
	c->next = NULL;
	return (c);
}

void	init_tkns(t_prompt *prompt)
{
	prompt->tkns = ft_calloc(sizeof (char *), MAX_TOKENS);
	if (!prompt->tkns)
	{
		free_all(prompt);
		exit (EXIT_FAILURE);
	}
}

void	init_env(t_prompt *prompt, char **env)
{
	t_env	*e;

	prompt->enviroment = ft_calloc(1, sizeof(t_env));
	if (!prompt->enviroment)
	{
		free_all(prompt);
		exit (EXIT_FAILURE);
	}
	e = prompt->enviroment;
	e->envp = env;
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

void	init_prompt(t_prompt *prompt, char **envp, int env)
{
	prompt->cmds = NULL;
	prompt->input = NULL;
	prompt->tkns = NULL;
	prompt->pid = 0;
	if (env)
		init_env(prompt, envp);
	init_tkns(prompt);
}

t_cmd	*create_cmd(t_prompt *prompt)
{
	t_cmd	*current;

	current = new_cmd();
	add_cmd_back(&prompt->cmds, current);
	return (current);
}
