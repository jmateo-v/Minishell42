/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:17:53 by dogs              #+#    #+#             */
/*   Updated: 2025/10/17 15:18:07 by dogs             ###   ########.fr       */
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