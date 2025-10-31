/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:48:43 by dogs              #+#    #+#             */
/*   Updated: 2025/10/24 11:13:34 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_translation(const char *line, int i, t_separator_ctx *ctx)
{
    i += 2;

    while (line[i] && line[i] != '"') 
    {
        if (ctx->buf_i < (int)sizeof(ctx->buffer) - 1)
            ctx->buffer[ctx->buf_i++] = line[i++];
    }

    if (line[i] != '"') 
    {
        write(2, "minishell: syntax error near unexpected token `\"'\n", 
              ft_strlen("minishell: syntax error near unexpected token `\"'\n"));
        return -1;
    }

    ctx->buffer[ctx->buf_i] = '\0';
    ctx->segments[ctx->seg_i].value = ft_strdup(ctx->buffer);
    ctx->segments[ctx->seg_i].type = QUOTE_TRANSLATION;
    ctx->seg_i++;
    ctx->buf_i = 0;

    return i;
}

