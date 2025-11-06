/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:09:22 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 15:54:06 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void	ft_free_env(t_shenv **env)
{
	t_shenv *node;
	t_shenv *next;

	if (!env || !*env)
		return ;
	node = *env;
	while (node)
	{
		next = node ->next;
		free(node->var);
		free(node);
		node = next;
	}
	*env = NULL;
}

int     ft_shenv_len(t_shenv *env)
{
        int     len;

        len = 0;
        if (!env)
                return (0);
        while (env)
        {
                len++;
                env = env->next;
        }
        return (len);
}

char    **ft_getshenv(t_shenv *env)
{
        t_shenv         *node;
        char    **r;
        int             len;
        int             i;

        if (!env)
                return (NULL);
        len = ft_shenv_len(env);
        r = (char **)ft_calloc(len + 1, sizeof(char *));
        if (!r)
                return (perror("minishell : malloc : "), NULL);
        i = 0;
        node = env;
        while (node)
        {
                r[i] = ft_strdup(node->var);
                if (node->var && !r[i])
                        return (perror("minishell : malloc : "), NULL);
                i++;
                node = node->next;
        }
        r[i] = NULL;
        return (r);
}

t_shenv *ft_load_env(char **envp)
{
        int             i;
        t_shenv *env;
        t_shenv *node;

        if (!envp)
                return (NULL);
        env = (t_shenv *)ft_calloc(1, sizeof(t_shenv));
        if (!env)
                return (perror("minishell : malloc : "), NULL);
        i = 0;
        node = env;
        while (envp[i])
        {
                node->var = ft_strdup(envp[i]);
                if (!node->var && envp[i] && envp[i][0])
                        return (ft_free_env(&env), perror("minishell : malloc : "), NULL);
                if (!envp[++i])
                        break ;
                node->next = (t_shenv *)ft_calloc(1, sizeof(t_shenv));
                if (!node->next)
                        return (ft_free_env(&env), perror("minishell : malloc : "), NULL);
                node = node->next;
        }
        return (node->next = NULL, env);
}