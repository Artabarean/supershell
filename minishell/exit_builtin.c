/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:05:50 by atabarea          #+#    #+#             */
/*   Updated: 2025/11/19 14:30:18 by atabarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool is_numeric(const char *s)
{
    int i = 0;

    if (s[i] == '+' || s[i] == '-')
        i++;

    if (!s[i])
        return (false);

    while (s[i]) {
        if (s[i] < '0' || s[i] > '9')
            return (false);
        i++;
    }
    return (true);
}

static long long ft_atoll(const char *str, bool *overflow)
{
    unsigned long long res = 0;
    int sign = 1;

    *overflow = false;

    if (*str == '-' || *str == '+') {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str) {
        res = res * 10 + (*str - '0');
        if ((sign == 1 && res > LLONG_MAX) ||
            (sign == -1 && res > (unsigned long long)LLONG_MAX + 1ULL)) {
            *overflow = true;
            return (0);
        }
        str++;
    }
    return ((long long)(res * sign));
}

int builtin_exit(char **args, int last_status)
{
	bool overflow;
	long long code;
	
    printf("exit\n");
    if (!args[1])
        exit(last_status);
    if (!is_numeric(args[1]))
	{
        fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
                args[1]);
        exit(2);
    }
    code = ft_atoll(args[1], &overflow);
    if (overflow)
	{
        fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
                args[1]);
        exit(2);
    }
    if (args[2])
	{
        fprintf(stderr, "minishell: exit: too many arguments\n");
        return (1);
    }
    exit((unsigned char)code);
}
