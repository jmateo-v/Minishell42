/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:59:13 by dogs              #+#    #+#             */
/*   Updated: 2025/10/24 11:20:06 by dogs             ###   ########.fr       */
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
        if (ctx->current_type == QUOTE_LITERAL_DOLLAR)
            flush_segment_with_type(ctx, QUOTE_LITERAL_DOLLAR);
        else
            flush_segment_with_type(ctx, QUOTE_DOUBLE);

        ctx->state = QUOTE_NONE;
        ctx->current_type = QUOTE_NONE;
    }
}


