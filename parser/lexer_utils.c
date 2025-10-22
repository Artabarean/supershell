#include "parser.h"

char	*expand_var(char *str,t_env *enviroment)
{
	char	*exp_str;
	
	if (!str || !*str)
		return (ft_strdup(""));
	if (!ft_strncmp(str, "PATH", 4))
		exp_str = ft_strdup(enviroment->path);
	else if (!ft_strncmp(str, "HOME", 4))
		exp_str = ft_strdup(enviroment->home);
	else if (!ft_strncmp(str, "PWD", 3))
		exp_str = ft_strdup(enviroment->pwd);
	else if (!ft_strncmp(str, "OLDPWD", 6))
		exp_str = ft_strdup(enviroment->oldpwd);
	else if (!ft_strncmp(str, "USER", 4))
		exp_str = ft_strdup(enviroment->user);
	else if (!ft_strncmp(str, "SHELL", 5))
		exp_str = ft_strdup(enviroment->shell);
	else if (!ft_strncmp(str, "SHLVL", 5))
		exp_str = ft_strdup(ft_itoa(enviroment->shlvl));
	else if (!ft_strncmp(str, "_", 1))
		exp_str = ft_strdup(enviroment->cmdpath);
	else
		exp_str = ft_strdup("");
	return (exp_str);
}

char	*expand(char **imput, t_env *enviroment)
{
	int		len;
	char	*temp;
	char	*var;

	len = 0;
	if (**imput == '$')
	{
		(*imput)++;
		while (ft_isalnum(**imput) || **imput == '_')
		{
			(*imput)++;
			len++;
		}
		temp = ft_substr(*imput - len, 0, len);
		var = expand_var(temp, enviroment);
		free(temp);
		if (!var)
			return (NULL);
		return (var);
	}
	else
		return (NULL);
}

char	*extract_str_quote(char **imput)
{
	int	len;
	char *temp;
	
	len = 0;
	while ((*imput)[len] && (*imput)[len] != '$' && (*imput)[len] != '"')
		len++;
	temp = ft_substr(*imput, 0, len);
	if (!temp)
		return (NULL);
	(*imput) += len;;
	return (temp);
}

char	*expand_or_empty(char **imput, t_env *env)
{
	char	*var;

	var = expand(imput, env);
	if (!var)
		var = ft_strdup("");
	return (var);
}

char	*handle_quote_content(char **imput, t_env *env)
{
	char	*buffer;
	char	*temp;
	char	*var;

	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	while (**imput && **imput != '"')
	{
		if (**imput == '$')
			var = expand_or_empty(imput, env);
		else
			var = extract_str_quote(imput);
		if (!var)
			return (free(buffer), NULL);
		temp = buffer;
		buffer = ft_strjoin_free(buffer, var);
	}
	return (buffer);
}






