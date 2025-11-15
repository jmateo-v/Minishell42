/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:44:27 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 12:49:24 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_quoted(const t_token *token)
{
	if (token == NULL)
		return (false);
	if (token->seg_type == QUOTE_SINGLE)
		return (true);
	else if (token->seg_type == QUOTE_DOUBLE)
		return (true);
	else if (token->seg_type == QUOTE_TRANSLATION)
		return (true);
	else if (token->seg_type == QUOTE_LITERAL)
		return (true);
	else
		return (false);
}

int	handle_append(t_token *tokens, t_cli *cli, t_parse_ctx *ctx)
{
	if (ctx->i + 1 >= ctx->len)
	{
		ft_perror("missing target for >>", SYN_ERR);
		ft_free_tokens(tokens);
		return (-2);
	}
	ft_append(tokens[ctx->i + 1].value, cli);
	return (2);
}

int	handle_trunc(t_token *tokens, t_cli *cli, t_parse_ctx *ctx)
{
	if (ctx->i + 1 >= ctx->len)
	{
		ft_perror("missing target for >", SYN_ERR);
		return (-2);
	}
	ft_trunc(tokens[ctx->i + 1].value, cli);
	return (2);
}

int	handle_infile(t_token *tokens, t_cli *cli, t_parse_ctx *ctx)
{
	if (ctx->i + 1 >= ctx->len)
	{
		ft_perror("missing target for <", SYN_ERR);
		return (-2);
	}
	ft_infile(tokens[ctx->i + 1].value, cli);
	return (2);
}

int	handle_pipe(t_token *tokens, t_cli **pcli, t_parse_ctx *ctx)
{
	t_cli	*cli;

	cli = *pcli;
	cli->next = ft_parse_pipe(tokens[ctx->i].value, cli);
	if (!cli->next)
		return (-2);
	*pcli = cli->next;
	return (1);
}
