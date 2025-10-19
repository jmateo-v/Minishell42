/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_finalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:19:33 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 10:43:58 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_token_finalize(t_token *tok)
{
    int   total_len = 0;
    int   i = 0;
    char *res;

    if (!tok || !tok->segments || !tok->segments[0].value)
        return (0);

    while (tok->segments[i].value)
    {
        total_len += (int)ft_strlen(tok->segments[i].value);
        i++;
    }

    res = malloc(total_len + 1);
    if (!res)
        return (0);

    res[0] = '\0';
    i = 0;
    while (tok->segments[i].value)
    {
        ft_strcat(res, tok->segments[i].value);
        i++;
    }

    tok->value = res;

    tok->quote_type = tok->segments[0].type;

    return (1);
}

void ft_finalize_tokens(t_token *tokens)
{
    int i = 0;

    while (tokens[i].segments)
    {
        if (!tokens[i].value)
            ft_token_finalize(&tokens[i]);
        i++;
    }
}