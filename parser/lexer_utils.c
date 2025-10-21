#include "parser.h"

char	*expand_var(char *str, t_prompt *prompt)
{
	char	*exp_str;
	
	if (!str || !*str)
		return (ft_strdup(""));
	if (!ft_strncmp(str, "PATH", 4))
		exp_str = ft_strdup(prompt->enviroment->path);
	else if (!ft_strncmp(str, "HOME", 4))
		exp_str = ft_strdup(prompt->enviroment->home);
	else if (!ft_strncmp(str, "PWD", 3))
		exp_str = ft_strdup(prompt->enviroment->pwd);
	else if (!ft_strncmp(str, "OLDPWD", 6))
		exp_str = ft_strdup(prompt->enviroment->oldpwd);
	else if (!ft_strncmp(str, "USER", 4))
		exp_str = ft_strdup(prompt->enviroment->user);
	else if (!ft_strncmp(str, "SHELL", 5))
		exp_str = ft_strdup(prompt->enviroment->shell);
	else if (!ft_strncmp(str, "SHLVL", 5))
		exp_str = ft_strdup(ft_itoa(prompt->enviroment->shlvl));
	else if (!ft_strncmp(str, "_", 1))
		exp_str = ft_strdup(prompt->enviroment->cmdpath);
	else
		exp_str = ft_strdup("");
	return (exp_str);
}

char	*extract_and_expand(t_prompt *prompt, int index)
{
	char	*buffer;
	char	*temp;
	char	*var;
	size_t	start;

	buffer = ft_strdup("");
	if (prompt->imput[index] == '"')
		index++;
	while (prompt->imput[index] && prompt->imput[index] != '"')
	{
		if (prompt->imput[index] == '$')
		{
			index++;
			start = index;
			while (ft_isalnum(prompt->imput[index]) || prompt->imput[index] == '_')
				index++;
			var = ft_substr(prompt->imput, start, index - start);
			temp = expand_var(var, prompt);
			buffer = ft_strjoin(buffer, temp);
			free(var);
			free(temp);
		}
		else
		{
			start = index;
			while (prompt->imput[index] && prompt->imput[index] != '$' && prompt->imput[index] != '"')
				index++;
			temp = ft_substr(prompt->imput, start, index - start);
			buffer = ft_strjoin(buffer, temp);
			free(temp);
		}
	}
	return (buffer);
}

char	*extract_str(t_prompt *prompt, int index)
{
	int	i;
	int len;
	char *str;

	i = 0;
	str = NULL;
	if (prompt->imput[index] == '"')
		str = extract_and_expand(prompt, index);
	else if (prompt->imput[index] == '\'')
	{
		index++;
		len = index;
		while(prompt->imput[len] != '\0' && prompt->imput[len] != '\'')
			len++;
		str = ft_substr(&prompt->imput[index], 0, len);
		if (!str)
			return (NULL);
	}
	else
		return (NULL);
	return (str);
}

int	ft_chrcmpr( char prompt, char sym)
{
	if (prompt == sym)
		return (1);
	else
		return (0);
}

void	init_tkns(char **tkns)
{
	tkns = malloc(sizeof(char*) * MAX_TOKENS);
    if (!tkns)
        //free_all ; ?
		exit (EXIT_FAILURE);
}
