/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape_sequence.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:39:43 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 19:01:01 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_single_quote_escape(t_separator_ctx *ctx, int i)
{
	ctx->buffer[ctx->buf_i++] = '\\';
	return (i + 1);
}

static int	handle_double_quote_escape(const char *line, int i,
										t_separator_ctx *ctx)
{
	char	next;

	next = line[i + 1];
	if (next == '"' || next == '\\' || next == '$' || next == '`')
	{
		ctx->buffer[ctx->buf_i++] = next;
		if (next == '$')
			ctx->current_type = QUOTE_LITERAL;
		return (i + 2);
	}
	ctx->buffer[ctx->buf_i++] = '\\';
	return (i + 1);
}

static int	handle_unquoted_escape(const char *line, int i,
									t_separator_ctx *ctx)
{
	char	next;

	next = line[i + 1];
	if (next)
	{
		ctx->buffer[ctx->buf_i++] = next;
		if (next == '$')
			ctx->current_type = QUOTE_LITERAL;
		return (i + 2);
	}
	ctx->buffer[ctx->buf_i++] = '\\';
	return (i + 1);
}

int	handle_escape_sequence(const char *line, int i, t_separator_ctx *ctx)
{
	if (ctx->quote_state == QSTATE_SINGLE)
		return (handle_single_quote_escape(ctx, i));
	if (ctx->quote_state == QSTATE_DOUBLE)
		return (handle_double_quote_escape(line, i, ctx));
	return (handle_unquoted_escape(line, i, ctx));
}
