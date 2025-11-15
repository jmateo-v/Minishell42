/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:28:49 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 12:51:07 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_missing_target(t_token *tokens, t_parse_ctx *ctx)
{
	if (ctx->i + 1 >= ctx->len)
	{
		ft_perror("missing target for <<", SYN_ERR);
		ft_free_tokens(tokens);
		return (-2);
	}
	return (0);
}

static t_heredoc	init_heredoc(t_token *tokens, t_parse_ctx *ctx)
{
	t_heredoc	hd;

	hd.delimiter = ft_strdup(tokens[ctx->i + 1].value);
	hd.quoted = is_quoted(&tokens[ctx->i + 1]);
	hd.fd = -1;
	return (hd);
}

static int	expand_heredocs(t_cli *cli, t_heredoc new_hd)
{
	t_heredoc	*expanded;

	expanded = ft_realloc(cli->heredocs,
			sizeof(t_heredoc) * cli->num_heredocs,
			sizeof(t_heredoc) * (cli->num_heredocs + 1));
	if (!expanded)
	{
		perror("realloc");
		return (-1);
	}
	cli->heredocs = expanded;
	cli->heredocs[cli->num_heredocs++] = new_hd;
	return (0);
}

static int	handle_noninteractive(t_token *tokens, t_cli *cli, t_parse_ctx *ctx)
{
	int	status;

	if (!isatty(STDIN_FILENO))
	{
		status = ft_script_heredoc(tokens[ctx->i + 1].value, cli);
		if (status != 0)
			return (-2);
	}
	return (0);
}

int	handle_heredoc(t_token *tokens, t_cli *cli, t_parse_ctx *ctx)
{
	t_heredoc	new_hd;
	int			ret;

	ret = check_missing_target(tokens, ctx);
	if (ret != 0)
		return (ret);
	new_hd = init_heredoc(tokens, ctx);
	ret = expand_heredocs(cli, new_hd);
	if (ret != 0)
		return (ret);
	ret = handle_noninteractive(tokens, cli, ctx);
	if (ret != 0)
		return (ret);
	return (2);
}
