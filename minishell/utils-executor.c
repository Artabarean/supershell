/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:26:01 by gcollet           #+#    #+#             */
/*   Updated: 2026/01/12 17:08:03 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
//No compruebas lo que devuelve find_path_no_print
//si no encuentra el comando no imprime command not found
void	check_command(t_cmd *cmd, t_prompt *prompt)
{
	t_cmd	*copy;

	copy = cmd;
	while (copy)
	{
		if (is_builtin(copy) == 0)
		{
			if (copy->full_cmd[0] != NULL)
			{
				if (!ft_strchr(copy->full_cmd[0], '/'))
					find_path_no_print(copy, prompt);
			}
			if (copy->full_cmd[0] == NULL)
				exit(0);
		}
		copy = copy->next;
	}
}
void	error_no_exit(char *s)
{
	s = ft_strjoin("minishell: ", s);
	perror(s);
}

void	error(char *s)
{
	s = ft_strjoin("minishell: ", s);
	perror(s);
	exit(EXIT_FAILURE);
}
//la variable prompt->enviroment->envp no está iniciada en ningún sitio
//creo que es mejor no crearla al iniciar el enviroment porque puede cambiar al hacer EXPORT
//se puede crear un char **envp en esta función y liberarlo después de execve

void	execute(char **full_cmd, char *full_path, t_prompt *prompt)
{
	char **envp;
	
	if (!full_path)
		exit(EXIT_FAILURE);
	envp = env_to_envp(prompt->enviroment);
	if (execve(full_path, full_cmd, envp) == -1)
	{
		err = errno;
		free_doble_ptr(envp);
		error_no_exit(full_path);
		if (err == ENOENT)
			exit(127);
		else if(err == EACCES)
			exit(126);
		else
			exit(1);
	}
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

int	pipecount(t_prompt prompt)
{
	t_cmd	*node_num;
	int		i;

	i = 0;
	node_num = prompt.cmds;
	while (node_num)
	{
		node_num = node_num->next;
		i++;
	}
	return (i - 1);
}