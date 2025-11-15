/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:01:23 by dogs              #+#    #+#             */
/*   Updated: 2025/11/11 18:02:57 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_command(t_cli *cmd)
{
	char	**env;
	int		status;

	env = ft_getshenv(*(cmd->env));
	if (cmd->env && !env)
		exit(2);
	if (cmd->is_builtin)
	{
		status = execute_builtin(cmd);
		ft_free_str_array(&env);
		exit(status);
	}
	check_command_errors(cmd);
	execve(cmd->cmd, cmd->args, env);
	perror("execve");
	ft_free_str_array(&env);
	if (errno == ENOENT || errno == ENOEXEC)
		exit(127);
	else
		exit(126);
}
