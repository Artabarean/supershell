#include "parser.h"

char	*extract_str(char **input)
{
	int		len;
	char	*start;
	char	*word;

	len = 0;
	if (**input == '\'')
	{
		(*input)++;
		start = *input;
		while (**input != '\'')
		{
			len++;
			(*input)++;
		}
		word = ft_substr(start, 0, len);
		if (!word)
			return (NULL);
		if (**input == '\'')
			(*input)++;
	}
	return (word);
}

char	*extract_and_expand(char **input, t_env *env)
{
	char	*buffer;

	if (!input || !*input)
		return (NULL);
	if (**input == '$')
		return (expand_or_empty(input, env));
	if (**input == '"')
		(*input)++;
	buffer = handle_quote_content(input, env);
	if (**input == '"')
		(*input)++;
	return (buffer);
}

char	*extract_word(char **input)
{
	int		len;
	char	*start;
	char	*word;

	if (!input || !*input)
		return (NULL);
	start = *input;
	len = 0;
	while ((**input && **input != ' ')
		|| **input == '|' || **input == '<' || **input == '>')
	{
		len++;
		(*input)++;
	}
	word = ft_substr(start, 0, len);
	if (!word)
		return (NULL);
	while (**input == ' ')
		(*input)++;
	return (word);
}

void	extract_sym(char **ptr, t_prompt *prompt, int index)
{
	if (*(*ptr + 1) == '<' || *(*ptr + 1) == '>')
	{
		prompt->tkns[index] = ft_substr(*ptr, 0, 2);
		(*ptr)++;
	}
	else
		prompt->tkns[index] = ft_substr(*ptr, 0, 1);
	(*ptr)++;
}

void	lexer(t_prompt *prompt)
{
	int		i;
	char	*ptr;

	if (!prompt->input)
		return ;
	ptr = prompt->input;
	i = 0;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if (*ptr == '\'')
			prompt->tkns[i] = extract_str(&ptr);
		else if (*ptr == '"' || *ptr == '$')
			prompt->tkns[i] = extract_and_expand(&ptr, prompt->enviroment);
		else if (*ptr == '|' || *ptr == '<' || *ptr == '>')
			extract_sym(&ptr, prompt, i);
		else
			prompt->tkns[i] = extract_word(&ptr);
		if (!prompt->tkns[i] || prompt->tkns[i][0] == '\0')
			break ;
		i++;
	}
	prompt->tkns[i] = NULL;
	return ;
}
