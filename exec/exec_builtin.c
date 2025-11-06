/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:07:07 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 18:48:10 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin(t_cli *cmd)
{
	char	**env;

	if (!cmd || !cmd->cmd)
		return (printf("!cmd"), 1);
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd(cmd->args));
	else if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd->args, cmd->env));
	else if (!ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd->args));
	else if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd->args, cmd->env));
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(cmd->args, cmd->env));
	else if (!ft_strcmp(cmd->cmd, "env"))
	{
		env = ft_getshenv(*(cmd->env));
		if (!env && cmd->env)
			return (ft_putstr_fd(ERR_INVALID_ENV, 2), 1);
		return (ft_env(env));
	}
	else if (!ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(cmd->args, cmd->last_status));
	return (1);
}
