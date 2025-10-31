/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/10/30 19:43:37 by dansanc3         ###   ########.fr       */
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

        /* if we have '||' or '&&' skip the duplicate operator token */
        if (i + 1 < len && tokens[i].value && tokens[i + 1].value)
        {
            if ((tokens[i].value[0] == '|' && tokens[i + 1].value[0] == '|')
                || (tokens[i].value[0] == '&' && tokens[i + 1].value[0] == '&'))
                i++;
        }
        i++;
    }

    return 0;
}
