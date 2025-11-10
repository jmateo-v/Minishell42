/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:31:13 by dogs              #+#    #+#             */
/*   Updated: 2025/11/10 17:53:10 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(t_shenv *env, char *name)
{
	size_t	len;

	len = ft_strlen(name);
	while (env)
	{
		if (env->var && ft_strncmp(env->var, name, len) == 0
			&& env->var[len] == '=')
			return (env->var + len + 1);
		env = env->next;
	}
	return (NULL);
}

static char	*build_env_var(char *key, char *value)
{
	int		key_len;
	int		value_len;
	char	*new_var;

	if (!key || !value)
		return (NULL);
	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	new_var = malloc(key_len + value_len + 2);
	if (!new_var)
		return (NULL);
	ft_strcpy(new_var, key);
	new_var[key_len] = '=';
	ft_strcpy(new_var + key_len + 1, value);
	return (new_var);
}

static int	update_existing_var(t_shenv *env, char *key, char *new_var)
{
	int	key_len;

	key_len = ft_strlen(key);
	while (env)
	{
		if (env->var && !ft_strncmp(env->var, key, key_len)
			&& env->var[key_len] == '=')
		{
			free(env->var);
			env->var = new_var;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static int	add_new_var(t_shenv **env, char *new_var)
{
	t_shenv	*new_node;

	new_node = ft_calloc(1, sizeof(t_shenv));
	if (!new_node)
		return (free(new_var), perror("malloc"), 1);
	new_node->var = new_var;
	new_node->next = *env;
	*env = new_node;
	return (0);
}

int	ft_setenv(t_shenv **env, char *key, char *value)
{
	char	*new_var;

	new_var = build_env_var(key, value);
	if (!new_var)
		return (perror("malloc"), 1);
	if (update_existing_var(*env, key, new_var))
		return (0);
	return (add_new_var(env, new_var));
}
