#include "parser.h"

void	parse_env(t_env *e, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			e->path = ft_strdup(env[i] + 5);
		else if (!ft_strncmp(env[i], "HOME=", 5))
			e->home = ft_strdup(env[i] + 5);
		else if (!ft_strncmp(env[i], "PWD=", 4))
			e->pwd = ft_strdup(env[i] + 4);
		else if (!ft_strncmp(env[i], "OLDPWD=", 7))
			e->oldpwd = ft_strdup(env[i] + 7);
		else if (!ft_strncmp(env[i], "USER=", 5))
			e->user = ft_strdup(env[i] + 5);
		else if (!ft_strncmp(env[i], "SHELL=", 6))
			e->shell = ft_strdup(env[i] + 6);
		else if (!ft_strncmp(env[i], "SHLVL=", 6))
			e->shlvl = ft_atoi(ft_strdup(env[i] + 6));
		else if (!ft_strncmp(env[i], "_=", 2))
			e->cmdpath = ft_strdup(env[i] + 2);
		i++;
	}
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