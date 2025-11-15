/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:08:21 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 21:10:06 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	setup_ctx(t_separator_ctx *ctx, char *line)
{
	if (!init_separator_ctx(ctx, line))
		return (false);
	return (true);
}

static void	finalize_ctx(t_separator_ctx *ctx)
{
	if (ctx->buf_i > 0)
		flush_segment_with_type(ctx, QUOTE_NONE);
	if (ctx->seg_i > 0)
		flush_token(ctx);
	ctx->tokens[ctx->token_i].segments = NULL;
	ctx->tokens[ctx->token_i].value = NULL;
}

static t_token	*handle_unclosed(char *line, t_separator_ctx *ctx)
{
	if (ctx->quote_state == QSTATE_SINGLE)
		write(2, "minishell: syntax error near unexpected token `''\n", 50);
	else
		write(2, "minishell: syntax error near unexpected token `\"'\n", 50);
	return (clean_err_return(line, ctx->segments, ctx->tokens));
}

static t_token	*cleanup_and_return(char *line, t_separator_ctx *ctx)
{
	free(ctx->segments);
	free(line);
	return (ctx->tokens);
}

t_token	*ft_token_sep(char *line)
{
	t_separator_ctx	ctx;

	if (!setup_ctx(&ctx, line))
		return (NULL);
	if (sep_loop(line, &ctx) < 0)
		return (clean_err_return(line, ctx.segments, ctx.tokens));
	finalize_ctx(&ctx);
	if (ctx.quote_state != QSTATE_NONE)
		return (handle_unclosed(line, &ctx));
	return (cleanup_and_return(line, &ctx));
}
