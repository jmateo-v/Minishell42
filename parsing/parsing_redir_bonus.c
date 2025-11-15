/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 12:14:04 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_bonus.h"

static int	handle_append(t_parse_ctx *ctx, int *i, t_cli *cli)
{
	if (!ctx->tokens[*i].value
		|| ft_strncmp(ctx->tokens[*i].value, ">>", 2))
		return (0);
	if (*i + 1 >= ctx->len)
		return (perror("missing target for >>, SYN ERR"),
			ft_free_tokens(ctx->tokens), 2);
	ft_append(ctx->tokens[*i + 1].value, cli);
	*i += 2;
	return (1);
}

static int	handle_heredoc(t_parse_ctx *ctx, int *i, t_cli *cli)
{
	if (!ctx->tokens[*i].value || ctx->tokens[*i].value[0] == '\0'
		|| ft_strcmp(ctx->tokens[*i].value, "<<"))
		return (0);
	if (*i + 1 >= ctx->len)
		return (ft_perror("missing target for <<", SYN_ERR),
			ft_free_tokens(ctx->tokens), 2);
	if (ft_heredoc(ctx->tokens[*i + 1].value, cli) == 130)
		return (130);
	*i += 2;
	return (1);
}

static int	handle_outfile(t_parse_ctx *ctx, int *i, t_cli *cli)
{
	if (!ctx->tokens[*i].value
		|| ft_strncmp(ctx->tokens[*i].value, ">", 1)
		|| ft_strlen(ctx->tokens[*i].value) != 1)
		return (0);
	if (*i + 1 >= ctx->len)
		return (ft_perror("missing target for >", SYN_ERR), 2);
	ft_trunc(ctx->tokens[*i + 1].value, cli);
	*i += 2;
	return (1);
}

static int	handle_infile(t_parse_ctx *ctx, int *i, t_cli *cli)
{
	if (!ctx->tokens[*i].value
		|| ft_strncmp(ctx->tokens[*i].value, "<", 1)
		|| ft_strlen(ctx->tokens[*i].value) != 1)
		return (0);
	if (*i + 1 >= ctx->len)
		return (ft_perror("missing target for <", SYN_ERR), 2);
	ft_infile(ctx->tokens[*i + 1].value, cli);
	*i += 2;
	return (1);
}

int	handle_redir(t_parse_ctx *ctx, int *i, t_cli *cli)
{
	int	ret;

	ret = handle_append(ctx, i, cli);
	if (ret)
		return (ret);
	ret = handle_heredoc(ctx, i, cli);
	if (ret)
		return (ret);
	ret = handle_outfile(ctx, i, cli);
	if (ret)
		return (ret);
	return (handle_infile(ctx, i, cli));
}
