/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape_sequence.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:39:43 by dogs              #+#    #+#             */
/*   Updated: 2025/10/17 16:41:00 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_escape_sequence(const char *line, int i,
                           char *buffer, int *buf_i,
                           t_quote_type state,
                           t_quote_type *current_type)
{
    int count = 0;
    while (line[i + count] == '\\')
        count++;

    char next = line[i + count];

    if (next == '$') {
        int pairs = count / 2;
        for (int k = 0; k < pairs; k++)
            buffer[(*buf_i)++] = '\\';

        if (count % 2 == 1) {
            buffer[(*buf_i)++] = '$';
            *current_type = QUOTE_LITERAL_DOLLAR;
        } else {
            buffer[(*buf_i)++] = '$';
        }
        return i + count;
    }

    if (next == '|' || next == '<' || next == '>') {
        int pairs = count / 2;
        for (int k = 0; k < pairs; k++)
            buffer[(*buf_i)++] = '\\';
        if (count % 2 == 1) {
            buffer[(*buf_i)++] = next;
            return i + count;
        } else {
            return i + count - 1;
        }
    }

    if (state == QUOTE_DOUBLE) {
        if (next == '"' || next == '\\' || next == '$' || next == '`') {
            if (next == '$' && (count % 2 == 1)) {
                buffer[(*buf_i)++] = '$';
                *current_type = QUOTE_LITERAL_DOLLAR;
            } else {
                buffer[(*buf_i)++] = next;
            }
            return i + count;
        } else {
            buffer[(*buf_i)++] = '\\';
            return i + 1;
        }
    }

    if (state == QUOTE_SINGLE) {
        buffer[(*buf_i)++] = '\\';
        return i + 1;
    }

    int pairs = count / 2;
    for (int k = 0; k < pairs; k++)
        buffer[(*buf_i)++] = '\\';
    if (count % 2 == 1 && next) {
        buffer[(*buf_i)++] = next;
        return i + count;
    } else {
        return i + count - 1;
    }
}
