/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:59:13 by dogs              #+#    #+#             */
/*   Updated: 2025/10/17 17:17:14 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_quote_open(char c,
                      char *buffer, int *buf_i,
                      t_segment *segments, int *seg_i,
                      t_quote_type *current_type,
                      t_quote_type *state)
{
    if (*buf_i > 0)
        flush_segment(buffer, buf_i, segments, seg_i, current_type);

    if (c == '\'')
        *state = QUOTE_SINGLE;
    else if (c == '"')
        *state = QUOTE_DOUBLE;

    return 0;
}
void handle_quote_close(char c,
                        char *buffer, int *buf_i,
                        t_segment *segments, int *seg_i,
                        t_quote_type *current_type,
                        t_quote_type *state)
{
    if (c == '\'' && *state == QUOTE_SINGLE)
    {
        flush_segment_with_type(buffer, buf_i, segments, seg_i, QUOTE_SINGLE);
        *state = QUOTE_NONE;
        *current_type = QUOTE_NONE;
    }
    else if (c == '"' && *state == QUOTE_DOUBLE)
    {
        if (*current_type == QUOTE_LITERAL_DOLLAR)
            flush_segment_with_type(buffer, buf_i, segments, seg_i, QUOTE_LITERAL_DOLLAR);
        else
            flush_segment_with_type(buffer, buf_i, segments, seg_i, QUOTE_DOUBLE);

        *state = QUOTE_NONE;
        *current_type = QUOTE_NONE;
    }
}

