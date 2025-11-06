/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:59:13 by dogs              #+#    #+#             */
/*   Updated: 2025/11/04 23:23:57 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_quote_open(char c, t_separator_ctx *ctx)
{
    if (ctx->buf_i > 0)
        flush_segment(ctx);

    if (c == '\'')
        ctx->state = QUOTE_SINGLE;
    else if (c == '"')
        ctx->state = QUOTE_DOUBLE;

    return 0;
}

void handle_quote_close(char c, t_separator_ctx *ctx)
{
    if (c == '\'' && ctx->state == QUOTE_SINGLE)
    {
        flush_segment_with_type(ctx, QUOTE_SINGLE);
        ctx->state = QUOTE_NONE;
        ctx->current_type = QUOTE_NONE;
    }
    else if (c == '"' && ctx->state == QUOTE_DOUBLE)
    {
        if (ctx->current_type == QUOTE_LITERAL)
            flush_segment_with_type(ctx, QUOTE_LITERAL);
        else
            flush_segment_with_type(ctx, QUOTE_DOUBLE);

        ctx->state = QUOTE_NONE;
        ctx->current_type = QUOTE_NONE;
    }
}
int handle_ansi_c_quote(const char *line, int i, t_separator_ctx *ctx)
{
    i += 2;
    while (line[i]) {
        if (line[i] == '\\' && line[i+1]) {
            if (ctx->buf_i < (int)sizeof(ctx->buffer) - 1)
                ctx->buffer[ctx->buf_i++] = line[i+1];
            i += 2;
            continue;
        }
        if (line[i] == '\'') {
            if (ctx->buf_i > 0) flush_segment(ctx);
            return i;
        }
        if (ctx->buf_i < (int)sizeof(ctx->buffer) - 1)
            ctx->buffer[ctx->buf_i++] = line[i];
        i++;
    }
    write(2, "minishell: syntax error: unclosed $'…'\n", 39);
    return -1;
}








