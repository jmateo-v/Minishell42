/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_helpers_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:28:16 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/11/21 14:35:12 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_bonus.h"

int check_logic(t_token *tokens, int n_tokens, int i)
{
    t_token *tok = &tokens[i];

    if (tok->token_type == T_LOGIC_OP)
    {
        if (i == 0 || i == n_tokens - 1)
            return (ft_perror(tok->value, ERR_LOGIC_OP), 1);

        if (tokens[i-1].token_type != T_WORD &&
            tokens[i-1].token_type != T_CL_BRACKETS)
            return (ft_perror(tok->value, ERR_LOGIC_OP), 1);

        if (tokens[i+1].token_type != T_WORD &&
            tokens[i+1].token_type != T_OP_BRACKETS)
            return (ft_perror(tok->value, ERR_LOGIC_OP), 1);
    }
    else if (tok->token_type == T_OP_BRACKETS)
    {
        if (i+1 >= n_tokens)
            return (ft_perror("(", ERR_PARENTHESIS), 1);

        if (tokens[i+1].token_type != T_WORD &&
            tokens[i+1].token_type != T_OP_BRACKETS)
            return (ft_perror("(", ERR_PARENTHESIS), 1);
    }
    else if (tok->token_type == T_CL_BRACKETS)
    {
        if (i == 0)
            return (ft_perror(")", ERR_PARENTHESIS), 1);

        if (tokens[i-1].token_type != T_WORD &&
            tokens[i-1].token_type != T_CL_BRACKETS)
            return (ft_perror(")", ERR_PARENTHESIS), 1);
    }
    return (0);
}
