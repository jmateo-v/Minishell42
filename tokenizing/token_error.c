/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:17:53 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 12:27:00 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int new_ft_check_errors(t_token *tokens, int n_tokens)
{
    int i = 0;
    if (!tokens || n_tokens == 0)
        return (ft_perror("(null)", ERR_NULL_TOKEN), 1);

    while (i < n_tokens)
    {
        if (!tokens[i].value)
            return (ft_perror("(null)", ERR_EMPTY_TOKEN), 1);
        if (tokens[i].token_type == T_REDIRECTION)
        {
            if (i + 1 >= n_tokens || tokens[i + 1].token_type != T_WORD)
                return (ft_perror(tokens[i].value, ERR_MISSING_REDIR_TARGET), 1);
        }
        if (tokens[i].token_type == T_OPERATOR && strcmp(tokens[i].value, "|") == 0)
        {
            if (i == 0)
                return (ft_perror("|", PIPE_ERR), 1);
            if (i == n_tokens - 1)
                return (ft_perror("|", PIPE_ERR), 1);
            if (i + 1 >= n_tokens || tokens[i + 1].token_type != T_WORD)
                return (ft_perror(tokens[i].value, PIPE_ERR), 1);
        }
        i++;
    }
    return (0);
}
