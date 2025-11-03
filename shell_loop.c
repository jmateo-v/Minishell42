/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:56 by dogs              #+#    #+#             */
/*   Updated: 2025/11/03 00:00:35 by dogs             ###   ########.fr       */
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

        if (!cl || cl[0] == '\0')
        {
            free(cl);
            return NULL;
        }
    }
    else
    {
        //rl_outstream = stderr;
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


int ft_process_command(char *cl, t_cli *cli)
{
    if (!cl || cl[0] == '\0')
        return 1;
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
        rl_event_hook = ft_sig_hook;
        cl = ft_read_input();
        rl_event_hook = NULL;
        if (g_sig_rec)
        {
            ft_reset_signal(cli);
            continue;
        }
        if (!cl)
        {
            if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
                write(1, "exit\n", 5);
            break;
        }
        if (cl[0] == '\0')
        {
            free(cl);
            continue;
        }
        cli->status = ft_process_command(cl, cli);
        cli->last_status = cli->status;
    }
        rl_clear_history();
        return cli->status;
}



