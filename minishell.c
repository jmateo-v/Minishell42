/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:07:34 by dogs              #+#    #+#             */
/*   Updated: 2025/11/04 23:00:39 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shenv		*env;
	t_cli		*cli;
	int			status;

	(void)argc;
	(void)argv;
	cli = ft_setup_shell(envp, &env);
	if (!cli)
		return (ft_free_env(&env), 2);
	status = shell_loop(cli);
	ft_cleanup_shell(&cli, &env);
	return (status);
}
