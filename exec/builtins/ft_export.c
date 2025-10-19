/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:36:55 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/10/18 17:14:50 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int is_valid_identifier(const char *str)
{
    int i;
    if (!str || !*str)
        return (0);

    if (!(ft_isalpha((unsigned char)str[0]) || str[0] == '_'))
        return (0);
    i = 1;
    while (str[i])
    {
        if (!(ft_isalnum((unsigned char)str[i]) || str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}
static void print_export(t_shenv *env)
{
    t_shenv *curr = env;
    char *eq;

    while (curr)
    {
        ft_putstr_fd("declare -x ", 1);

        eq = ft_strchr(curr->var, '=');
        if (eq)
        {
            write(1, curr->var, eq - curr->var);
            ft_putstr_fd("=\"", 1);
            ft_putstr_fd(eq + 1, 1);
            ft_putstr_fd("\"", 1);
        }
        else
        {
            ft_putstr_fd(curr->var, 1);
        }

        ft_putstr_fd("\n", 1);
        curr = curr->next;
    }
}


int ft_export(char **args, t_shenv **env)
{
    int i;
    char *eq;
    char *key;
    char *value;

    if (!args[1])
    {
        print_export(*env);
        return (0);
    }
    i = 1;
    while (args[i])
    {
        eq = ft_strchr(args[i], '=');
        if(eq)
        {
            key = ft_strndup(args[i], eq - args [i]);
            value = ft_strdup(eq + 1);
            if (!is_valid_identifier(key))
            {
                free(key);
                free(value);
                ft_putstr_fd("Not a valid identifier\n", 2);
                return (1);
            }
            else
                ft_setenv(env, key, value);
            free(key);
            free(value);
        }
        else
        {
            if (!is_valid_identifier(args[i]))
            {
                ft_putstr_fd("Not a valid identifier\n", 2);
                return (1);
            }
            else
            {
                if(!ft_getenv(*env, args[i]))
                    ft_setenv(env, args[i], "");
            }
        }
        i++;
    }
    return (0);
}