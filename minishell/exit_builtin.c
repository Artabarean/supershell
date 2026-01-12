/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medel-ca <medel-ca@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:05:50 by atabarea          #+#    #+#             */
/*   Updated: 2026/01/12 16:23:08 by medel-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	checkforexit(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->full_cmd[0], "exit"))
	{
		if (cmd->full_cmd[2])
			return (1);
	}
	return (0);
}

static bool	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (false);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static long long	ft_atoll(const char *str, bool *overflow)
{
	unsigned long long	res;
	int					sign;

	res = 0;
	sign = 1;
	*overflow = false;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		res = res * 10 + (*str - '0');
		if ((sign == 1 && res > LLONG_MAX) || (sign == -1
				&& res > (unsigned long long)LLONG_MAX + 1ULL))
		{
			*overflow = true;
			return (0);
		}
		str++;
	}
	return ((long long)(res * sign));
}
//	Los mensajes de error van a stderror
//	El g_exit_status no se actualiza bien
int	exit_builtin(t_cmd *cmd, t_prompt *prompt)
{
	bool		overflow;
	long long	code;

	printf("exit\n");
	if (!cmd->full_cmd[1])
		exit(pid_stat(cmd, prompt, 0));
	if (!is_numeric(cmd->full_cmd[1]))
	{
		ft_putendl_fd(" numeric argument required", 2);
		free_all(prompt);
		exit(2);
	}
	code = ft_atoll(cmd->full_cmd[1], &overflow);
	if (overflow)
	{
		ft_putendl_fd(" numeric argument required", 2);
		free_all(prompt);
		exit(2);
	}
	if (cmd->full_cmd[2])
		return (ft_putendl_fd(" too many arguments", 2), 1);
	free_all(prompt);
	exit((unsigned char)code);
}
