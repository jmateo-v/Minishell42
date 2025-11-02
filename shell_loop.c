/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:56 by dogs              #+#    #+#             */
/*   Updated: 2025/11/02 19:19:20 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_read_input(void)
{
    char *cl = NULL;

    if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
    {
        rl_outstream = stderr;
        cl = readline("\033[1;38;5;117mminishell\033[0m$ ");
        if (!cl)
            write(1, "exit\n", 5);
    }
    else
    {
        cl = get_next_line(STDIN_FILENO);
        if (cl)
        {
            size_t len = ft_strlen(cl);
            if (len > 0 && cl[len - 1] == '\n')
                cl[len - 1] = '\0';
        }
    }
    return cl;
}
bool ft_check_signal_interrupt(char *cl, t_cli *cli)
{
    if (g_sig_rec && ft_reset_signal(cli))
        return true;
    if (cl[0] != '\0')
        add_history(cl);
    return false;
}

int ft_process_command(char *cl, t_cli *cli)
{
    t_token *tokens = ft_tokenize_cl(cl, cli);
    if (!tokens)
        return 2;
    //print_tokens(tokens);
    cli->status = ft_parse(tokens, cli);
    //ft_print_list(cli);
    cli->status = ft_execute(cli);
    ft_free_tokens(tokens);
    ft_reset_list(cli);
    return cli->status;
}

int shell_loop(t_cli *cli)
{
    char *cl = NULL;

    while (1)
    {
        if (cl)
            free(cl);
        cl = ft_read_input();
        if (!cl)
            break;
        if (ft_check_signal_interrupt(cl, cli))
            continue;
        cli->status = ft_process_command(cl, cli);
        if (!isatty(STDIN_FILENO))
            continue;
        cli->last_status = cli->status;
    }
    rl_clear_history();
    return cli->status;
}
