/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:29:01 by dogs              #+#    #+#             */
/*   Updated: 2025/10/30 18:19:16 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void add_operator_token(char c, const char *line, int *i, t_separator_ctx *ctx)
{
    char buffer[3];

    buffer[0] = c;
    if ((c == '>' || c == '<') && line[*i + 1] == c) {
        buffer[1] = c;
        buffer[2] = '\0';
        (*i)++;
    } else {
        buffer[1] = '\0';
    }

    ctx->tokens[ctx->token_i].segments = ft_calloc(2, sizeof(t_segment));
    if (!ctx->tokens[ctx->token_i].segments)
        return;

    ctx->tokens[ctx->token_i].segments[0].value = ft_strdup(buffer);

    if (buffer[0] == '>' || buffer[0] == '<') {
        ctx->tokens[ctx->token_i].segments[0].type = REDIRECTION;
        ctx->tokens[ctx->token_i].token_type = T_REDIRECTION;
    } else {
        ctx->tokens[ctx->token_i].segments[0].type = OPERATOR;
        ctx->tokens[ctx->token_i].token_type = T_OPERATOR;
    }

    ctx->tokens[ctx->token_i].segments[1].value = NULL;

    ctx->tokens[ctx->token_i].value = ft_strdup(buffer);

    ctx->token_i++;
}


void handle_operator(char c, char *line, int *i, t_separator_ctx *ctx)
{
    if (ctx->buf_i > 0)
        flush_segment(ctx);

    if (ctx->seg_i > 0)
    {
        flush_token(ctx);
        ctx->seg_i = 0;
    }

    add_operator_token(c, line, i, ctx);
    ctx->seg_i= 0;
}
