/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:48:43 by dogs              #+#    #+#             */
/*   Updated: 2025/11/04 20:30:03 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_translation(const char *line, int i, t_separator_ctx *ctx)
{
    i += 2;

    while (line[i] && line[i] != '"') {
        if (ctx->buf_i < (int)sizeof(ctx->buffer) - 1)
            ctx->buffer[ctx->buf_i++] = line[i];
        i++;
    }

    if (line[i] != '"') {
        write(2, "minishell: syntax error near unexpected token `\"'\n", 50);
        return -1;
    }

    return i;
}


