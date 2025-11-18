/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:43:30 by alex              #+#    #+#             */
/*   Updated: 2025/11/17 14:24:06 by atabarea         ###   ########.fr       */
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
	prompt.pfd = malloc(sizeof(int[2]) * (n_cmds - 1));
	if (!prompt.pfd)
		error("malloc");
	while (i < n_cmds - 1)
	{
		if (pipe(prompt.pfd[i]) == -1)
			error("pipe");
		i++;
	}
	i = 0;
	while (i < n_cmds && cmd)
	{
		selectprocess(&prompt, cmd, i, filein, fileout);
		cmd = cmd->next;
		i++;
	}
	closepfds(n_cmds, prompt);
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
			if (cmd->append == 1)
				*fileout = open_file(cmd->outfile[i], 0);
			else
				*fileout = open_file(cmd->outfile[i], 1);
			if (cmd->outfile[i + 1] != NULL && cmd->next != NULL)
			{
				close(*fileout);
				*fileout = -1;
			}
			i++;
		}
		i = 0;
		while (cmd->infile[i])
		{
			*filein = open_file(cmd->infile[i], 2);
			if (cmd->infile[i + 1] != NULL && cmd->next != NULL)
			{
				close(*filein);
				*filein = -1;
			}
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

	printf("status:%d\n", status);
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
	printf("openfile:%d\n", i);
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error("open");
	return (file);
}
