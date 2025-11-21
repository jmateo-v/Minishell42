/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/21 16:18:20 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_bonus.h"

static int	check_null_or_empty(t_token *tokens, int n_tokens, int i)
{
	if (!tokens || n_tokens == 0)
		return (ft_perror("(null)", ERR_NULL_TOKEN), 1);
	if (!tokens[i].value)
		return (ft_perror("(null)", ERR_EMPTY_TOKEN), 1);
	return (0);
}

static int	check_redirection(t_token *tokens, int n_tokens, int i)
{
	if (tokens[i].token_type == T_REDIRECTION)
	{
		if (i + 1 >= n_tokens || tokens[i + 1].token_type != T_WORD)
			return (ft_perror(tokens[i].value, ERR_MISSING_REDIR_TARGET), 1);
	}
	return (0);
}

static int	check_pipe(t_token *tokens, int n_tokens, int i)
{
	if (tokens[i].token_type == T_OPERATOR
		&& ft_strcmp(tokens[i].value, "|") == 0)
	{
		if (i == 0 || i == n_tokens - 1)
			return (ft_perror("|", PIPE_ERR), 1);
		if (tokens[i - 1].token_type != T_WORD
			&& tokens[i - 1].token_type != T_CL_BRACKETS)
			return (ft_perror(tokens[i].value, PIPE_ERR), 1);
		if (tokens[i + 1].token_type != T_WORD
			&& tokens[i + 1].token_type != T_OP_BRACKETS)
			return (ft_perror(tokens[i].value, PIPE_ERR), 1);
	}
	return (0);
}

static int	check_parenthesis_balance(t_token *tokens, int n_tokens)
{
	int	balance;
	int	i;

	balance = 0;
	i = 0;
	while (i < n_tokens)
	{
		if (tokens[i].token_type == T_OP_BRACKETS)
			balance++;
		else if (tokens[i].token_type == T_CL_BRACKETS)
			balance--;
		if (balance < 0)
			return (ft_perror(")", ERR_PARENTHESIS), 1);
		i++;
	}
	if (balance != 0)
		return (ft_perror("(", ERR_PARENTHESIS), 1);
	return (0);
}

int	ft_check_errors(t_token *tokens, int n_tokens)
{
	int	i;
	int	err;

	i = -1;
	if (!tokens || n_tokens == 0)
		return (ft_perror("(null)", ERR_NULL_TOKEN), 1);
	while (++i < n_tokens)
	{
		err = check_null_or_empty(tokens, n_tokens, i);
		if (err)
			return (err);
		err = check_redirection(tokens, n_tokens, i);
		if (err)
			return (err);
		err = check_pipe(tokens, n_tokens, i);
		if (err)
			return (err);
		err = check_logic(tokens, n_tokens, i);
		if (err)
			return (err);
	}
	err = check_parenthesis_balance(tokens, n_tokens);
	if (err)
		return (err);
	return (0);
}
