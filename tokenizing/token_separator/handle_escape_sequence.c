/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape_sequence.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:39:43 by dogs              #+#    #+#             */
/*   Updated: 2025/11/04 23:03:28 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_escape_sequence(const char *line, int i, t_separator_ctx *ctx)
{
    char next = line[i+1];

    if (ctx->quote_state == QSTATE_SINGLE) {
        ctx->buffer[ctx->buf_i++] = '\\';
        return i + 1;
    }

    if (ctx->quote_state == QSTATE_DOUBLE) {
        if (next == '"' || next == '\\' || next == '$' || next == '`') {
            ctx->buffer[ctx->buf_i++] = next;
            if (next == '$')
                ctx->current_type = QUOTE_LITERAL;
            return i + 2;
        } else {
            ctx->buffer[ctx->buf_i++] = '\\';
            return i + 1;
        }
    }
    if (next) {
        ctx->buffer[ctx->buf_i++] = next;
        if (next == '$')
            ctx->current_type = QUOTE_LITERAL;
        return i + 2;
    } else {
        ctx->buffer[ctx->buf_i++] = '\\';
        return i + 1;
    }
}



