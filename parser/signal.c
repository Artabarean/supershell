#include "parser.h"

void	set_signal(int status, t_prompt *prompt)
{
	if (status == EXIT)
	{
		printf("Exit\n");
		free_all(prompt);
		exit(EXIT_SUCCESS);
	}
	else
		printf("Otras formas de salir según el estado\n");
}
