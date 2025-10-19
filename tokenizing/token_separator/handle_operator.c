/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:29:01 by dogs              #+#    #+#             */
/*   Updated: 2025/10/17 17:34:54 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void add_operator_token(char c, const char *line, int *i,
                               t_token *tokens, int *token_i)
{
    char buffer[3];

    buffer[0] = c;
    if ((c == '>' || c == '<') && line[*i + 1] == c) {
        buffer[1] = c;
        buffer[2] = '\0';
        (*i)++;
    } else {
        buffer[1] = '\0';
    }

    tokens[*token_i].segments = ft_calloc(2, sizeof(t_segment));
    tokens[*token_i].segments[0].value = ft_strdup(buffer);
    tokens[*token_i].segments[0].type  = OPERATOR;
    (*token_i)++;
}
void handle_operator(char c, char *line, int *i,
                     char *buffer, int *buf_i,
                     t_segment *segments, int *seg_i,
                     t_quote_type *current_type,
                     t_token *tokens, int *token_i)
{
    if (*buf_i > 0)
        flush_segment(buffer, buf_i, segments, seg_i, current_type);

    if (*seg_i > 0)
    {
        flush_token(segments, *seg_i, tokens, token_i);
        *seg_i = 0;
    }

    add_operator_token(c, line, i, tokens, token_i);
}
