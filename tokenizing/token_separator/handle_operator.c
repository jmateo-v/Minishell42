/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:29:01 by dogs              #+#    #+#             */
/*   Updated: 2025/11/19 18:43:25 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	build_operator_buffer(char c, const char *line,
									int *i, char buffer[3])
{
	buffer[0] = c;
	if ((c == '>' || c == '<') && line[*i + 1] == c)
	{
		buffer[1] = c;
		buffer[2] = '\0';
		(*i)++;
	}
	else
		buffer[1] = '\0';
}

int	init_token_segments(t_token *token, const char *buffer)
{
	token->segments = ft_calloc(2, sizeof(t_segment));
	if (!token->segments)
		return (0);
	token->segments[0].value = ft_strdup(buffer);
	token->segments[1].value = NULL;
	return (1);
}

static void	set_token_type(t_token *token, const char *buffer)
{
	if (buffer[0] == '>' || buffer[0] == '<')
	{
		token->segments[0].type = REDIRECTION;
		token->token_type = T_REDIRECTION;
	}
	else
	{
		token->segments[0].type = OPERATOR;
		token->token_type = T_OPERATOR;
	}
}

void	add_operator_token(char c, const char *line,
							int *i, t_separator_ctx *ctx)
{
	char	buffer[3];
	t_token	*token;

	build_operator_buffer(c, line, i, buffer);
	token = &ctx->tokens[ctx->token_i];
	if (!init_token_segments(token, buffer))
		return ;
	set_token_type(token, buffer);
	token->value = ft_strdup(buffer);
	ctx->token_i++;
}

void	handle_operator(char c, char *line, int *i, t_separator_ctx *ctx)
{
	if (ctx->buf_i > 0)
		flush_segment(ctx);
	if (ctx->seg_i > 0)
	{
		flush_token(ctx);
		ctx->seg_i = 0;
	}
	add_operator_token(c, line, i, ctx);
	ctx->seg_i = 0;
}
