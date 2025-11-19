/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:30 by alex              #+#    #+#             */
/*   Updated: 2025/11/19 12:42:52 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int pid_stat(t_cmd *curr_nde ,t_prompt prompt, int status, int last_status)
{
	int	i;
	int	n_cmds;

	i = 0;
	n_cmds = pipecount(prompt);
    while (i < n_cmds && curr_nde)
	{
		waitpid(prompt.pid[i], &status, 0);
		if (curr_nde->next == NULL)
			last_status = status;
		curr_nde = curr_nde->next;
		i++;
	}
    return (last_status);
}

void    childprocess_(t_cmd *cmd, int filein, int fileout, t_prompt prompt)
{
    int	i;
	int	n_cmds;

	i = 0;
	n_cmds = pipecount(prompt) + 1;
	pfd_alloc(&prompt, n_cmds);
	while (i < n_cmds - 1)
	{
		if (pipe(prompt.pfd[i]) == -1)
			error("Pipe failed");
		i++;
	}
	i = 0;
	while (i < n_cmds && cmd)
	{
		selectprocess(&prompt, cmd, i, filein, fileout);
		cmd = cmd->next;
		i++;
	}
	closepfds(n_cmds, &prompt);
	while (n_cmds > 0)
	{
		wait(NULL);
		n_cmds--;
	}
}

void    file_opener(t_prompt prompt, int *fileout, int *filein)
{
    int 	i;
	t_cmd	*cmd;

	cmd = prompt.cmds;
    i = 0;
    while (cmd)
	{
		while (cmd->outfile[i])
		{
			find_outfile(cmd, i, fileout);
			i++;
		}
		i = 0;
		while (cmd->infile[i])
		{
			find_infile(cmd, i, filein);
			i++;
		}
		i = 0;
		cmd = cmd->next;
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
		error("Open failed");
	return (file);
}
