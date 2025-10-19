/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:42:25 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 11:11:17 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cli   *ft_parse_pipe(char *token, t_cli *cli)
{
    t_cli   *next_cli;

    if (!token || !cli)
        return (perror("parse op !token || !cli"), NULL);
    if (token[0] != '|')
        return (perror("invalid token parse_op"), NULL);

    cli->op = (cli->breaks_pipe) ? NO_OP : PIPE;
    if (cli->op == NO_OP)
        cli->group++;

    next_cli = ft_init_node(cli->n_tokens, cli->env, 0);
    if (!next_cli)
        return (perror("malloc : "), cli->status = 2, NULL);

    next_cli->n_tokens = 1;
    cli->next = next_cli;
    return (next_cli);
}
