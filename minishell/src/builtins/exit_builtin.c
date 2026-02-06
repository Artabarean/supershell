/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:05:50 by atabarea          #+#    #+#             */
/*   Updated: 2026/02/06 11:48:07 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_num_arg_req(t_prompt *prompt, char *cmd)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free(prompt->pid);
	free_all(prompt);
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

void	exit_builtin(t_cmd *cmd, t_prompt *prompt)
{
	bool		overflow;
	long long	code;

	if (!cmd->full_cmd[1])
		exit(0);
	if (!is_numeric(cmd->full_cmd[1]))
	{
		print_num_arg_req(prompt, cmd->full_cmd[1]);
		exit(2);
	}
	code = ft_atoll(cmd->full_cmd[1], &overflow);
	if (overflow)
	{
		print_num_arg_req(prompt, cmd->full_cmd[1]);
		exit(2);
	}
	if (cmd->full_cmd[2])
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		prompt->exit_status = 1;
		return ;
	}
	free_all(prompt);
	exit((unsigned char)code);
}
