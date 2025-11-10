/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:52:27 by dogs              #+#    #+#             */
/*   Updated: 2025/11/10 18:04:00 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_cd_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static char	*resolve_cd_target(char **args, t_shenv *env)
{
	if (!args[1] || !args[1][0])
		return (ft_getenv(env, "HOME"));
	if (ft_strcmp(args[1], "-") == 0)
		return (ft_getenv(env, "OLDPWD"));
	return (args[1]);
}

static void	update_cd_env(t_shenv **env, char *old_pwd)
{
	char	cwd[PATH_MAX];

	ft_setenv(env, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)))
		ft_setenv(env, "PWD", cwd);
}

int	ft_cd(char **args, t_shenv **env)
{
	char	cwd[PATH_MAX];
	char	*target;

	if (check_cd_args(args))
		return (1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("cd: getcwd"), 1);
	target = resolve_cd_target(args, *env);
	if (!target)
	{
		ft_putstr_fd("cd: target not found\n", 2);
		return (1);
	}
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		ft_putendl_fd(target, 1);
	if (chdir(target) != 0)
	{
		perror("cd");
		return (1);
	}
	update_cd_env(env, cwd);
	return (0);
}
