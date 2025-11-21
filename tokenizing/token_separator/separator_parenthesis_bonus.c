/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_parenthesis_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:01:05 by dogs              #+#    #+#             */
/*   Updated: 2025/11/21 13:51:14 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../include/minishell_bonus.h"

static void	set_token_type(t_token *token, char *buffer)
{
	if (buffer[0] == '(')
	{
		token->segments[0].type = OP_BRACKETS;
		token->token_type = T_OP_BRACKETS;
	}
	else
	{
		token->segments[0].type = CL_BRACKETS;
		token->token_type = T_CL_BRACKETS;
	}
}

static void	add_parenthesis_token(char c, t_separator_ctx *ctx)
{
	char	buffer[2];
	t_token	*token;

	buffer[0] = c;
	buffer[1] = '\0';
	token = &ctx->tokens[ctx->token_i];
	if (!init_token_segments(token, buffer))
		return ;
	set_token_type(token, buffer);
	token->value = ft_strdup(buffer);
	ctx->token_i++;
}

static void	handle_parenthesis(char *line, int *i, t_separator_ctx *ctx)
{
	if (ctx->buf_i > 0)
		flush_segment(ctx);
	if (ctx->seg_i > 0)
	{
		flush_token(ctx);
		ctx->seg_i = 0;
	}
	add_parenthesis_token(line[*i], ctx);
	ctx->seg_i = 0;
}

int	handle_parenthesis_char(char *line, int i, t_separator_ctx *ctx)
{
	handle_parenthesis(line, &i, ctx);
	return (i + 1);
}
