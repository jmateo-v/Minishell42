/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:07:34 by dogs              #+#    #+#             */
/*   Updated: 2025/10/23 18:36:41 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shenv		*env;
	extern int	rl_catch_signals;
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
