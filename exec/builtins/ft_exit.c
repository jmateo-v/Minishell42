/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:16:26 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 15:45:44 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_numeric(const char *str)
{
    int i;

    if (!str || !*str)
        return 0;

    i = 0;
    if (str[0] == '+' || str[0] == '-')
        i = 1;

    if (!str[i])
        return 0;

    for (; str[i]; i++)
    {
        if (!ft_isdigit((unsigned char)str[i]))
            return 0;
    }
    return 1;
}

int ft_exit(char **args, int last_status)
{
    long long val;
    int status;
    
    status =last_status;
    if (isatty(STDIN_FILENO))
        write(1, "exit\n", 5);

    if (args[1])
    {
        if (!is_numeric(args[1]))
        {
            write(2, "exit: ", 6);
            write(2, args[1], strlen(args[1]));
            write(2, ": numeric argument required\n", 29);
            exit(2);
        }
        if (args[2])
        {
            write(2, "exit: too many arguments\n", 25);
            return 1;
        }
        val = ft_atoll(args[1]);
        status = (unsigned char)val;
    }
    exit(status);
}