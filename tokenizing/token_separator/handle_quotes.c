/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:59:13 by dogs              #+#    #+#             */
/*   Updated: 2025/11/04 21:31:25 by dogs             ###   ########.fr       */
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
    // at i: '$', i+1: '\''
    i += 2; // skip $'
    while (line[i]) {
        if (line[i] == '\\' && line[i+1]) {
            // For now: copy escaped char literally; extend to full ANSI-C if desired
            if (ctx->buf_i < (int)sizeof(ctx->buffer) - 1)
                ctx->buffer[ctx->buf_i++] = line[i+1];
            i += 2;
            continue;
        }
        if (line[i] == '\'') {
            // closing quote
            // Optionally flush here if you want each $'…' to be a segment:
            if (ctx->buf_i > 0) flush_segment(ctx);
            return i; // index of closing '
        }
        if (ctx->buf_i < (int)sizeof(ctx->buffer) - 1)
            ctx->buffer[ctx->buf_i++] = line[i];
        i++;
    }
    // unclosed
    write(2, "minishell: syntax error: unclosed $'…'\n", 39);
    return -1;
}








