/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_loop_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:54:21 by dogs              #+#    #+#             */
/*   Updated: 2025/11/21 14:18:00 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../include/minishell_bonus.h"

static int	handle_dollar_cases(char *line, int i, t_separator_ctx *ctx)
{
	if (line[i + 1] == '"' && line[i + 2])
	{
		i = handle_translation_char(line, i, ctx);
		if (i < 0)
			return (-1);
	}
	else if (line[i + 1] == '\'' && line[i + 2])
	{
		i = handle_ansi_c_char(line, i, ctx);
		if (i < 0)
			return (-1);
	}
	else
		i = handle_unquoted_char(line[i], i, ctx);
	return (i);
}

static int	handle_none_state(char *line, int i, t_separator_ctx *ctx)
{
	char	c;

	c = line[i];
	if (c == '\\')
	{
		i = handle_escape(line, i, ctx);
		if (i < 0)
			return (-1);
	}
	else if (c == '(' || c == ')')
		i = handle_parenthesis_char(line, i, ctx);
	else if ((c == '&' && line[i+1] == '&') || (c == '|' && line[i+1] == '|'))
		i = handle_logic_operator(line, i, ctx);
	else if (c == '>' || c == '<' || (c == '|' && line[i + 1] != '|'))
		i = handle_operator_char(c, line, i, ctx);
	else if (c == '$')
		i = handle_dollar_cases(line, i, ctx);
	else
		i = handle_unquoted_char(c, i, ctx);
	return (i);
}

static int	handle_single_state(char c, int i, t_separator_ctx *ctx)
{
	return (handle_single_quote_char(c, i, ctx));
}

static int	handle_double_state(char c, int i, t_separator_ctx *ctx)
{
	return (handle_double_quote_char(c, i, ctx));
}

int	sep_loop(char *line, t_separator_ctx *ctx)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		c = line[i];
		if (ctx->quote_state == QSTATE_NONE)
			i = handle_none_state(line, i, ctx);
		else if (ctx->quote_state == QSTATE_SINGLE)
			i = handle_single_state(c, i, ctx);
		else if (ctx->quote_state == QSTATE_DOUBLE)
			i = handle_double_state(c, i, ctx);
		if (i < 0)
			return (-1);
	}
	return (i);
}
