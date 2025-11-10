/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:36:55 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/11/10 18:23:56 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

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

static void	print_export(t_shenv *env)
{
	t_shenv	*curr;
	char	*eq;

	curr = env;
	while (curr)
	{
		ft_putstr_fd("export ", 1);
		if (curr->var)
		{
			eq = ft_strchr(curr->var, '=');
			if (eq)
			{
				write(1, curr->var, eq - curr->var);
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(eq + 1, 1);
				ft_putstr_fd("\"", 1);
			}
			else
				ft_putstr_fd(curr->var, 1);
		}
		ft_putstr_fd("\n", 1);
		curr = curr->next;
	}
}

static int	export_with_value(char *arg, t_shenv **env)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	key = ft_strndup(arg, eq - arg);
	value = ft_strdup(eq + 1);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("Not a valid identifier\n", 2);
		free(key);
		free(value);
		return (1);
	}
	ft_setenv(env, key, value);
	free(key);
	free(value);
	return (0);
}

static int	export_without_value(char *arg, t_shenv **env)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("Not a valid identifier\n", 2);
		return (1);
	}
	if (!ft_getenv(*env, arg))
		ft_setenv(env, arg, "");
	return (0);
}

int	ft_export(char **args, t_shenv **env)
{
	int	i;

	if (!args[1])
	{
		print_export(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (export_with_value(args[i], env))
				return (1);
		}
		else if (export_without_value(args[i], env))
			return (1);
		i++;
	}
	return (0);
}
