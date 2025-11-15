/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:30:15 by dogs              #+#    #+#             */
/*   Updated: 2025/11/10 17:09:38 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_sig_rec = 0;

int	ft_sig_hook(void)
{
	if (g_sig_rec)
	{
		rl_done = 1;
	}
	return (0);
}

void	enable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ft_sig_int_parent(int sig)
{
	(void)sig;
	g_sig_rec = 1;
	write(STDOUT_FILENO, "^C", 2);
}

int	ft_reset_signal(t_cli *cli)
{
	g_sig_rec = 0;
	ft_reset_list(cli);
	cli->last_status = 130;
	return (1);
}
