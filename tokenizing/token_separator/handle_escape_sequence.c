/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape_sequence.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:39:43 by dogs              #+#    #+#             */
/*   Updated: 2025/10/24 10:41:26 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_escape_sequence(const char *line, int i, t_separator_ctx *ctx)
{
    int count = 0;
    while (line[i + count] == '\\')
        count++;

    char next = line[i + count];

    if (next == '$')
    {
        int pairs = count / 2;
        for (int k = 0; k < pairs; k++)
            ctx->buffer[ctx->buf_i++] = '\\';

        if (count % 2 == 1)
        {
            ctx->buffer[ctx->buf_i++] = '$';
            ctx->current_type = QUOTE_LITERAL_DOLLAR;
        } else
        {
            ctx->buffer[ctx->buf_i++] = '$';
        }
        return i + count;
    }

    if (next == '|' || next == '<' || next == '>') {
        int pairs = count / 2;
        for (int k = 0; k < pairs; k++)
            ctx->buffer[ctx->buf_i++] = '\\';
        if (count % 2 == 1) {
            ctx->buffer[ctx->buf_i++] = next;
            return i + count;
        } else {
            return i + count - 1;
        }
    }

    if (ctx->state == QUOTE_DOUBLE) {
        if (next == '"' || next == '\\' || next == '$' || next == '`') {
            if (next == '$' && (count % 2 == 1)) {
                ctx->buffer[ctx->buf_i++] = '$';
                ctx->current_type = QUOTE_LITERAL_DOLLAR;
            } else {
                ctx->buffer[ctx->buf_i++] = next;
            }
            return i + count;
        } else {
            ctx->buffer[ctx->buf_i++] = '\\';
            return i + 1;
        }
    }

    if (ctx->state == QUOTE_SINGLE) {
        ctx->buffer[ctx->buf_i++] = '\\';
        return i + 1;
    }

    int pairs = count / 2;
    for (int k = 0; k < pairs; k++)
        ctx->buffer[ctx->buf_i++] = '\\';
    if (count % 2 == 1 && next) {
        ctx->buffer[ctx->buf_i++] = next;
        return i + count;
    } else {
        return i + count - 1;
    }
}
