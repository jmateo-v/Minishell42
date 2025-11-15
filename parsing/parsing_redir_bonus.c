/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 13:18:10 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../include/minishell_bonus.h"

static int	bonus_handle_append(t_b_parse_ctx *ctx, int *i, t_cli *cli)
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

static int	bonus_handle_heredoc(t_b_parse_ctx *ctx, int *i, t_cli *cli)
{
	if (!ctx->tokens[*i].value || ctx->tokens[*i].value[0] == '\0'
		|| ft_strcmp(ctx->tokens[*i].value, "<<"))
		return (0);
	if (*i + 1 >= ctx->len)
		return (ft_perror("missing target for <<", SYN_ERR),
			ft_free_tokens(ctx->tokens), 2);
	if (ft_script_heredoc(ctx->tokens[*i + 1].value, cli) == 130)
		return (130);
	*i += 2;
	return (1);
}

static int	bonus_handle_outfile(t_b_parse_ctx *ctx, int *i, t_cli *cli)
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

static int	bonus_handle_infile(t_b_parse_ctx *ctx, int *i, t_cli *cli)
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

int	handle_redir(t_b_parse_ctx *ctx, int *i, t_cli *cli)
{
	int	ret;

	ret = bonus_handle_append(ctx, i, cli);
	if (ret)
		return (ret);
	ret = bonus_handle_heredoc(ctx, i, cli);
	if (ret)
		return (ret);
	ret = bonus_handle_outfile(ctx, i, cli);
	if (ret)
		return (ret);
	return (bonus_handle_infile(ctx, i, cli));
}
