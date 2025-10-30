/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:30 by alex              #+#    #+#             */
/*   Updated: 2025/10/30 20:00:15 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int pid_stat(t_cmd *curr_nde ,t_prompt prompt, int status, int last_status)
{
    while (curr_nde)
	{
		waitpid(prompt.pid, &status, 0);
		if (curr_nde->next == NULL)
			last_status = status;
		curr_nde = curr_nde->next;
	}
    return (last_status);
}

void    childprocess_(t_cmd *curr_nde, int filein, int fileout, t_prompt prompt)
{
    int i;

    i = 0;
    while (curr_nde)
	{
		if (i == 0)
		{
			printf("Llamada a la función child_process1\n");
		//	child_process1(curr_nde, filein, fileout, prompt);
		}
		if (i != 0 && curr_nde->next != NULL)
		{
			printf("Llamada a la función child_processmid\n");
		//	child_processmid(curr_nde, prompt);
		}
		if (curr_nde->next == NULL)
		{
			printf("Llamada a la función child_processend\n");
		//	child_processend(curr_nde, filein, fileout, prompt);
		}
		curr_nde = curr_nde->next;
        i++;
	}
}

void    file_opener(t_prompt prompt, int fileout, int filein)
{
    int i;

    i = 0;
    while (prompt.cmds->outfile[i])
	{
		fileout = open_file(prompt.cmds->outfile[i], 1);
		if (prompt.cmds->outfile[i++] == NULL)
			break ;
		close(fileout);
		fileout = -1;
		i++;
	}
	i = 0;
	while (prompt.cmds->infile[i])
	{
		filein = open_file(prompt.cmds->infile[i], 2);
		if (prompt.cmds->infile[i++] == NULL)
			break;
		close(filein);
		filein = -1;
		i++;
	}
}

void	check_status(int status)
{
	int exit_code;
    int signal_num;

    if ((status & 0x7F) == 0)
    {
        exit_code = (status >> 8) & 0xFF;
        printf("Exited with code %d\n", exit_code);
    }
    else
    {
        signal_num = status & 0x7F;
        // In Bash, exit code = 128 + signal
        exit_code = 128 + signal_num;
        printf("Killed by signal %d\n", signal_num);
    }
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}
