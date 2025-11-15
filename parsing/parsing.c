/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:55:04 by dogs              #+#    #+#             */
/*   Updated: 2025/11/13 02:33:50 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	dispatch_token(t_token *tokens, t_cli **pcli, t_parse_ctx *ctx)
{
	t_cli	*cli;
	t_token	*tok;

	cli = *pcli;
	tok = &tokens[ctx->i];
	if (tok->token_type == T_REDIRECTION && !ft_strncmp(tok->value, ">>", 2))
		return (handle_append(tokens, cli, ctx));
	if (tok->token_type == T_REDIRECTION && ft_strcmp(tok->value, "<<") == 0)
		return (handle_heredoc(tokens, cli, ctx));
	if (tok->token_type == T_REDIRECTION && !ft_strncmp(tok->value, ">", 1)
		&& ft_strlen(tok->value) == 1)
		return (handle_trunc(tokens, cli, ctx));
	if (tok->token_type == T_REDIRECTION && !ft_strncmp(tok->value, "<", 1)
		&& ft_strlen(tok->value) == 1)
		return (handle_infile(tokens, cli, ctx));
	if (tok->token_type == T_OPERATOR && is_pipe(tok->value))
		return (handle_pipe(tokens, pcli, ctx));
	ft_parse_token(tokens, ctx->i, cli, &ctx->group);
	return (1);
}

int	ft_parse_loop(t_token *tokens, t_cli *cli, t_parse_ctx *ctx)
{
	int	ret;
	int	consumed;

	while (ctx->i < ctx->len)
	{
		if (!tokens[ctx->i].value)
		{
			ctx->i++;
			continue ;
		}
		ret = dispatch_token(tokens, &cli, ctx);
		if (ret < 0)
			return (2);
		consumed = ret;
		ctx->i += consumed;
	}
	return (0);
}

int	ft_parse(t_token *tokens, t_cli *cli)
{
	t_parse_ctx	ctx;

	if (!tokens || !cli)
		return (2);
	ctx.i = 0;
	ctx.group = 1;
	ctx.len = ft_token_count(tokens);
	cli->n_tokens = 1;
	return (ft_parse_loop(tokens, cli, &ctx));
}
