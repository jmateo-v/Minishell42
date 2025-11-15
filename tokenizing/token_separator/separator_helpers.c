/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:10:43 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 21:10:58 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_escape(char *line, int i, t_separator_ctx *ctx)
{
	i = handle_escape_sequence(line, i, ctx);
	if (i < 0)
		return (-1);
	return (i);
}

int	handle_operator_char(char c, char *line, int i, t_separator_ctx *ctx)
{
	handle_operator(c, line, &i, ctx);
	return (i + 1);
}

int	handle_translation_char(char *line, int i, t_separator_ctx *ctx)
{
	int	new_i;

	if (ctx->buf_i > 0)
		flush_segment_with_type(ctx, QUOTE_NONE);
	new_i = handle_translation(line, i, ctx);
	if (new_i == -1)
		return (-1);
	return (new_i + 1);
}

int	handle_ansi_c_char(char *line, int i, t_separator_ctx *ctx)
{
	int	new_i;

	if (ctx->buf_i > 0)
		flush_segment_with_type(ctx, QUOTE_NONE);
	new_i = handle_ansi_c_quote(line, i, ctx);
	if (new_i == -1)
		return (-1);
	return (new_i + 1);
}

t_token	*clean_err_return(char *line, t_segment *segments,
								t_token *tokens)
{
	free(line);
	free(segments);
	ft_free_tokens(tokens);
	return (NULL);
}
