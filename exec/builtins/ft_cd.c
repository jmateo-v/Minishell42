/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:52:27 by dogs              #+#    #+#             */
/*   Updated: 2025/10/18 17:17:31 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_getenv(t_shenv *env, const char *key)
{
    int len;

    len = ft_strlen(key);
    while (env)
    {
        if (!ft_strncmp(env->var, key, len) && env->var[len] == '=')
            return(env->var + len + 1);
        env = env->next;
    }
    return NULL;
}
int ft_setenv(t_shenv **env, const char *key, const char *value)
{
    t_shenv *node;
    char *new_var;
    int key_len;
    t_shenv *new_node;

    node = *env;
    new_node = NULL;
    key_len = ft_strlen(key);
    new_var = malloc(key_len + ft_strlen(value) + 2);
    if (!new_var)
        return(perror("malloc"), 1);
    ft_strcpy(new_var, key);
    new_var[key_len] = '=';
    ft_strcpy(new_var + key_len + 1, value);
    while(node)
    {
        if(!ft_strncmp(node->var, key, key_len) && node->var[key_len] == '=')
        {
            free (node->var);
            node->var = new_var;
            return (0);
        }
        node = node->next;
    }
    new_node = ft_calloc(1, sizeof(t_shenv));
    if (!new_node)
        return (free(new_var), perror("malloc"), 1);
    new_node->var = new_var;
    new_node->next = *env;
    *env = new_node;
    return (0);
}

int ft_cd(char **args, t_shenv **env)
{
    char cwd[PATH_MAX];
    char *target;

    target = NULL;
    if (!getcwd(cwd, sizeof(cwd)))
        return(perror("cd: getcwd"), 1);
    if (!args[1] || !args[1][0])
        target = ft_getenv(*env, "HOME");
    else if (ft_strcmp(args[1], "-") == 0)
        target = ft_getenv(*env, "OLDPWD");
    else
        target = args[1];
    
    if (!target)
    {
        ft_putstr_fd("cd: target not found\n", 2);
        return(1);
    }
    if (chdir(target) != 0)
    {
        perror("cd");
        return (1);
    }
    ft_setenv(env, "OLDPWD", cwd);
    if (getcwd(cwd, sizeof(cwd)))
        ft_setenv(env, "PWD", cwd);
    return (0);
}