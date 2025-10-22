#include "parser.h"

char	*extract_str(char **imput)
{
	int		len;
	char	*start;
	char	*word;

	if (!imput || !*imput)
		return (NULL);
	len = 0;
	if (**imput == '\'')
	{
		(*imput)++;
		start = *imput;
		while(**imput != '\0' && **imput != '\'')
		{
			len++;
			(*imput)++;
		}
		word = ft_substr(start, 0, len);
		if (!word)
		return (NULL);
		if (**imput == '\'')
			(*imput)++;
	}
	else
		return (NULL);
	return (word);
}

char	*extract_and_expand(char **imput, t_env *env)
{
	char	*buffer;

	if (!imput || !*imput)
		return (NULL);
	if (**imput == '$')
		return (expand_or_empty(imput, env));
	if (**imput == '"')
		(*imput)++;
	buffer = handle_quote_content(imput, env);
	if (**imput == '"')
		(*imput)++;
	return (buffer);
}

char	*extract_word(char **imput)
{
	int		len;
	char	*start;
	char	*word;

	if (!imput || !*imput)
		return (NULL);
	start = *imput;
	len = 0;
	while (**imput && **imput != ' ' || **imput == '|' || **imput == '<' || **imput == '>')
	{
		len++;
		(*imput)++;
	}
	word = ft_substr(start, 0, len);
	if (!word)
		return (NULL);
	while (**imput == ' ')
		(*imput)++;
	return (word);
}

void	lexer(t_prompt *prompt)
{
	int		i;
	char	*ptr;

	if (!prompt->imput)
		return ;
	init_tkns(prompt);
	ptr = prompt->imput;
	i = 0;
	while (*ptr)
	{
		while (*ptr == ' ')
			ptr++;
		if (*ptr == '\'')
			prompt->tkns[i] = extract_str(&ptr);
		else if (*ptr == '"' || *ptr == '$')
			prompt->tkns[i] = extract_and_expand(&ptr, prompt->enviroment);
		else if (*ptr == '|' || *ptr == '<' || *ptr == '>')
		{
			if (*ptr + 1 == '<' || *ptr + 1 == '>')
			{
				prompt->tkns[i] = ft_substr(ptr, 0, 2);
				ptr++;
			}
			else
				prompt->tkns[i] = ft_substr(ptr, 0, 2);
    		ptr++;
		}
		else if (ft_isascii(*ptr))
			prompt->tkns[i] = extract_word(&ptr);
		if (!prompt->tkns[i])
			break;
		i++;
	}
	prompt->tkns[i] = NULL;
	return ;
}
