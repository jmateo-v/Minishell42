/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:30:15 by dogs              #+#    #+#             */
/*   Updated: 2025/11/03 17:53:40 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
volatile sig_atomic_t	g_sig_rec = 0;

int ft_sig_hook(void)
{
    if (g_sig_rec)
    {
        rl_done = 1;
    }
    return 0;
}

void enable_echoctl(void)
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void check_echoctl(void)
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    if (term.c_lflag & ECHOCTL)
        printf("ECHOCTL is enabled\n");
    else
        printf("ECHOCTL is disabled\n");
}

void ft_sig_int_parent(int sig)
{
    (void)sig;
    g_sig_rec = 1;
    write(STDOUT_FILENO, "^C", 2);
}

void ft_set_sig(int option)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    ft_memset(&sa_int, 0, sizeof(sa_int));
    ft_memset(&sa_quit, 0, sizeof(sa_quit));

    if (option == PARENT)
    {
        ft_memset(&sa_int, 0, sizeof(sa_int));

    sa_int.sa_handler = ft_sig_int_parent;
    sa_int.sa_flags = 0;

    sigaction(SIGINT, &sa_int, NULL);

    ft_memset(&sa_int, 0, sizeof(sa_int));
    sa_int.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa_int, NULL);
    }
    else if (option == CHILD)
    {
        sa_int.sa_handler = SIG_DFL;
        sigaction(SIGINT, &sa_int, NULL);
        sigaction(SIGQUIT, &sa_int, NULL);
    }
    else if (option == IGNORE)
    {
        sa_int.sa_handler = SIG_IGN;
        sigaction(SIGINT, &sa_int, NULL);
        sigaction(SIGQUIT, &sa_int, NULL);
    }
}

int ft_reset_signal(t_cli *cli)
{
    g_sig_rec = 0;
    ft_reset_list(cli);
    cli->last_status = 130;
    
    return 1;
}

