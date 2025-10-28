/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:17:53 by dogs              #+#    #+#             */
/*   Updated: 2025/10/24 11:22:59 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_check_errors(t_token *tokens, int len)
{
    int i = 0;
    int has_command = 0;

    while (i < len)
    {
        has_command = 0;

        while (i < len && !(tokens[i].value[0] == '|' && tokens[i].value[1] == '\0'))
        {
            char *curr = tokens[i].value;
            char *next = (i + 1 < len) ? tokens[i + 1].value : NULL;

            if (!curr || curr[0] == '\0') {
                i++;
                continue;
            }

            if (ft_strchr("<>", curr[0])) {
                if (!next || ft_strchr("|&", next[0]))
                    return (ft_perror(curr, SYN_ERR), 1);
            }

            if (!ft_strchr("|&<>", curr[0]))
                has_command = 1;

            i++;
        }

        if (!has_command)
            return (ft_perror(tokens[i].value, SYN_ERR), 1);

        i++;
    }

    return 0;
}

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
            if (i + 1 >= n_tokens)
                return (ft_perror(tokens[i].value, ERR_MISSING_REDIR_TARGET), 1);
            
        }
        if (tokens[i].token_type == T_OPERATOR && strcmp(tokens[i].value, "|") == 0)
        {
            if (i == 0)
                return (ft_perror("|", PIPE_ERR), 1);
            if (i == n_tokens - 1)
                return (ft_perror("|", PIPE_ERR), 1);
        }
        i++;
    }
    return (0);
}
