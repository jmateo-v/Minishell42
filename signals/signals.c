/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:30:15 by dogs              #+#    #+#             */
/*   Updated: 2025/10/18 15:30:17 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_sig_int_parent(int signal)
{
	char nl;

	nl = '\n';
    g_sig_rec = 1;
	if (signal == SIGINT)
	{
        write(1, "^C", 2);
        ioctl(STDIN_FILENO, TIOCSTI, &nl);
    }
}


void    ft_set_sig(int option)
{
    struct sigaction        sa;

    ft_memset(&sa, 0, sizeof(sa));
    if (option == PARENT)
    {
        sa.sa_handler = ft_sig_int_parent;
        sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
        sigaction(SIGQUIT, &sa, NULL);
    }
    if (option == CHILD)
    {
        sa.sa_handler = SIG_DFL;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
	}
    if (option == IGNORE)
    {
        sa.sa_handler = SIG_IGN;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
    }
	return ;
}
int	ft_reset_signal(t_cli *cli)
{
	g_sig_rec = 0;
	ft_reset_list(cli);
	cli->last_status = 130;
	return (1);
}