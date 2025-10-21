#include "parser.h"

void	lexer(t_prompt *prompt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	init_tkns(prompt->tkns);
	while (prompt->imput[j] != '\0')
	{
		if (prompt->imput[j] == ' ')
			j++;
		if (ft_chrcmpr(prompt->imput[j], '"') || ft_chrcmpr(prompt->imput[j], '\''))
		{
			prompt->tkns[i] = extract_str(prompt, j);
            j += ft_strlen(prompt->tkns[i]) + 2;
		}
		else if (ft_chrcmpr(prompt->imput[j], '$'))
		{			
			prompt->tkns[i] =extract_str(prompt, j);
			j += ft_strlen(prompt->tkns[i]) + 1;
		}
		else
		{
			prompt->tkns[i] = extract_word(prompt, j);
			j += ft_strlen(prompt->tkns[i]);
		}
		i++;
	}
	prompt->tkns[i] = NULL;
}
