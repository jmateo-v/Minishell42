/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_logic_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/19 18:51:43 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_bonus.h"

static int	create_next_cli(t_cli **cli, int step, int *i, int op)
{
	t_cli	*next;

	(*cli)->op = op;
	next = ft_init_node((*cli)->n_tokens, (*cli)->env, 0);
	if (!next)
		return (perror("malloc : "), 2);
	next->n_tokens = 1;
	(*cli)->next = next;
	*cli = next;
	*i += step;
	return (1);
}

int	process_and(t_b_parse_ctx *ctx, t_cli **cli, int *i)
{
	int	step;

	if (!ctx->tokens[*i].value)
		return (0);
	step = 0;
	if (strcmp(ctx->tokens[*i].value, "&&") == 0)
		step = 1;
	else if (strcmp(ctx->tokens[*i].value, "&") == 0
		&& (*i + 1) < ctx->len && ctx->tokens[*i + 1].value
		&& strcmp(ctx->tokens[*i + 1].value, "&") == 0)
		step = 2;
	if (!step)
		return (0);
	return (create_next_cli(cli, step, i, AND));
}

int	process_or(t_b_parse_ctx *ctx, t_cli **cli, int *i)
{
	int	step;

	if (!ctx->tokens[*i].value)
		return (0);
	step = 0;
	if (strcmp(ctx->tokens[*i].value, "||") == 0)
		step = 1;
	else if (strcmp(ctx->tokens[*i].value, "|") == 0
		&& (*i + 1) < ctx->len && ctx->tokens[*i + 1].value
		&& strcmp(ctx->tokens[*i + 1].value, "|") == 0)
		step = 2;
	if (!step)
		return (0);
	return (create_next_cli(cli, step, i, OR));
}
