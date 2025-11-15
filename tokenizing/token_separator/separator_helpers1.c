/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_helpers1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:11:51 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 19:31:38 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_whitespace_unquoted(t_separator_ctx *ctx, int i)
{
	if (ctx->buf_i > 0)
		flush_segment_with_type(ctx, QUOTE_NONE);
	if (ctx->seg_i > 0 || ctx->buf_i > 0)
	{
		flush_token(ctx);
		ctx->seg_i = 0;
	}
	return (i + 1);
}

int	handle_unquoted_char(char c, int i, t_separator_ctx *ctx)
{
	if (c == '\'')
	{
		if (ctx->buf_i > 0)
			flush_segment_with_type(ctx, QUOTE_NONE);
		ctx->quote_state = QSTATE_SINGLE;
		return (i + 1);
	}
	else if (c == '"')
	{
		if (ctx->buf_i > 0)
			flush_segment_with_type(ctx, QUOTE_NONE);
		ctx->quote_state = QSTATE_DOUBLE;
		return (i + 1);
	}
	else if (ft_isspace((unsigned char)c))
		return (handle_whitespace_unquoted(ctx, i));
	else
	{
		if (ctx->buf_i < (int) sizeof(ctx->buffer) - 1)
			ctx->buffer[ctx->buf_i++] = c;
		return (i + 1);
	}
}

int	handle_single_quote_char(char c, int i, t_separator_ctx *ctx)
{
	if (c == '\'')
	{
		ctx->quote_state = QSTATE_NONE;
		flush_segment_with_type(ctx, QUOTE_SINGLE);
		return (i + 1);
	}
	if (ctx->buf_i < (int) sizeof(ctx->buffer) - 1)
		ctx->buffer[ctx->buf_i++] = c;
	return (i + 1);
}

int	handle_double_quote_char(char c, int i, t_separator_ctx *ctx)
{
	if (c == '"')
	{
		flush_segment_with_type(ctx, QUOTE_DOUBLE);
		ctx->quote_state = QSTATE_NONE;
		return (i + 1);
	}
	if (ctx->buf_i < (int) sizeof(ctx->buffer) - 1)
		ctx->buffer[ctx->buf_i++] = c;
	return (i + 1);
}
