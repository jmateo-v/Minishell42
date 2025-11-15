/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 12:10:48 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_bonus.h"

static int	evaluate_ret(int ret)
{
	if (ret > 1)
		return (ret);
	return (0);
}

static int	process_pipe_token(t_parse_ctx *ctx, int index, t_cli **cli)
{
	if (!ctx->tokens[index].value
		|| !is_pipe(ctx->tokens[index].value))
		return (0);
	(*cli)->next = ft_parse_pipe(ctx->tokens[index].value, *cli);
	if (!(*cli)->next)
		return (2);
	*cli = (*cli)->next;
	return (1);
}

static int	process_token(t_parse_ctx *ctx, t_cli **cli, int *i, int *group)
{
	int	ret;

	ret = process_and(ctx, cli, i);
	if (ret)
		return (evaluate_ret(ret));
	ret = process_or(ctx, cli, i);
	if (ret)
		return (evaluate_ret(ret));
	ret = handle_redir(ctx, i, *cli);
	if (ret)
		return (evaluate_ret(ret));
	ret = process_pipe_token(ctx, *i, cli);
	if (ret)
	{
		if (ret != 1)
			return (ret);
		(*i)++;
		return (0);
	}
	ft_parse_token(ctx->tokens, *i, *cli, group);
	(*i)++;
	return (0);
}

static int	iterate_tokens(t_parse_ctx *ctx, t_cli *cli)
{
	int		ret;
	int		i;
	int		group;
	t_cli	*current;

	i = 0;
	group = 1;
	current = cli;
	while (i < ctx->len)
	{
		if (!ctx->tokens[i].value)
		{
			i++;
			continue ;
		}
		ret = process_token(ctx, &current, &i, &group);
		if (ret)
			return (ret);
	}
	return (0);
}

int	ft_parse(t_token *tokens, t_cli *cli)
{
	t_parse_ctx	ctx;

	if (!tokens || !cli)
		return (2);
	ctx.tokens = tokens;
	ctx.len = ft_token_count(tokens);
	cli->n_tokens = 1;
	return (iterate_tokens(&ctx, cli));
}
