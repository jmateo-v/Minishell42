/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:25:36 by dogs              #+#    #+#             */
/*   Updated: 2025/10/30 18:09:05 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *concat_segments(t_segment *segments, int seg_i)
{
    size_t total_len = 0;

    for (int i = 0; i < seg_i; i++)
        total_len += ft_strlen(segments[i].value);

    char *result = ft_calloc(total_len + 1, sizeof(char));
    if (!result)
        return NULL;

    for (int i = 0; i < seg_i; i++)
        ft_strcat(result, segments[i].value);

    return result;
}

void flush_segment(t_separator_ctx *ctx)
{
    ctx->buffer[ctx->buf_i] = '\0';
    ctx->segments[ctx->seg_i].value = ft_strdup(ctx->buffer);
    ctx->segments[ctx->seg_i].type  = ctx->current_type;
    ctx->seg_i++;
    ctx->buf_i = 0;
    ctx->current_type = QUOTE_NONE;
}

void flush_token(t_separator_ctx *ctx)
{
    t_token *tok = &ctx->tokens[ctx->token_i];

    tok->segments = ft_calloc(ctx->seg_i + 1, sizeof(t_segment));
    if (!tok->segments)
        return;

    ft_memcpy(tok->segments, ctx->segments, sizeof(t_segment) * ctx->seg_i);

    tok->value = concat_segments(ctx->segments, ctx->seg_i);

    tok->seg_type = ctx->segments[0].type;

    ctx->token_i++;
}

void flush_segment_with_type(t_separator_ctx *ctx, t_seg_type type)
{
    ctx->buffer[ctx->buf_i] = '\0';
    ctx->segments[ctx->seg_i].value = ft_strdup(ctx->buffer);
    ctx->segments[ctx->seg_i].type  = type;
    ctx->seg_i++;
    ctx->buf_i = 0;
}

int init_separator_ctx(t_separator_ctx *ctx, char *line)
{
    if (!ctx || !line)
        return 0;

    ctx->len = ft_strlen(line);
    ctx->state = QUOTE_NONE;
    ctx->current_type = QUOTE_NONE;
    ctx->buf_i = 0;
    ctx->token_i = 0;
    ctx->seg_i = 0;

    ft_memset(ctx->buffer, 0, sizeof(ctx->buffer));

    ctx->tokens = ft_calloc(ctx->len + 1, sizeof(t_token));
    ctx->segments = ft_calloc(ctx->len + 1, sizeof(t_segment));

    if (!ctx->tokens || !ctx->segments)
        return 0;

    return 1;
}
