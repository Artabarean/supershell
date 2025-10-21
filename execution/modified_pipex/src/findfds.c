/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findfds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:41:05 by alex              #+#    #+#             */
/*   Updated: 2025/10/21 10:56:02 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char    *findout(char *argv[], int argc)
{
    int     i;
    int     j;
    int     *letters;
    int     count;
    char    *result;

    letters = calloc(argc, sizeof(int));
    count = 0;
    i = 0;
    j = 0;
    while (argv[j])
    {
        while (argv[j][i])
        {
            if (argv[j][i] == '>' && (argv[j][i++] != '>' || argv[j][i++] != '\0'))
            {
                i++;
                while (argv[j][i] != '\0')
                    letters[count]++;
            }
            else
                i++;
        }
        count++;
        i = 0;
    }
    result = assignnames(letters, count, argv);
}
