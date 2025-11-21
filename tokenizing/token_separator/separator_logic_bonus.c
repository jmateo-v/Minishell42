/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_logic_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:57:07 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/11/21 16:10:28 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../include/minishell_bonus.h"

static void	set_token_type(t_token *token, char *buffer)
{
	if (buffer[0] == '&' && buffer[1] == '&')
	{
		token->segments[0].type = LOGICAL_OP;
		token->token_type = T_LOGIC_OP;
	}
	else if (buffer[0] == '|' && buffer[1] == '|')
	{
		token->segments[0].type = LOGICAL_OP;
		token->token_type = T_LOGIC_OP;
	}
}

static void	add_lop_token(char c, t_separator_ctx *ctx)
{
	char	buffer[3];
	t_token	*token;

	buffer[0] = c;
	buffer[1] = c;
	buffer[2] = '\0';
	token = &ctx->tokens[ctx->token_i];
	if (!init_token_segments(token, buffer))
		return ;
	set_token_type(token, buffer);
	token->value = ft_strdup(buffer);
	ctx->token_i++;
}

static void	handle_lop(char *line, int *i, t_separator_ctx *ctx)
{
	if (ctx->buf_i > 0)
		flush_segment(ctx);
	if (ctx->seg_i > 0)
	{
		flush_token(ctx);
		ctx->seg_i = 0;
	}
	add_lop_token(line[*i], ctx);
	ctx->seg_i = 0;
}

int	handle_logic_operator(char *line, int i, t_separator_ctx *ctx)
{
	handle_lop(line, &i, ctx);
	return (i + 2);
}
