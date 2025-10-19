/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:25:36 by dogs              #+#    #+#             */
/*   Updated: 2025/10/17 16:27:06 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void flush_segment(char *buffer, int *buf_i,
                          t_segment *segments, int *seg_i,
                          t_quote_type *current_type)
{
    buffer[*buf_i] = '\0';
    segments[*seg_i].value = ft_strdup(buffer);
    segments[*seg_i].type  = *current_type;
    (*seg_i)++;
    *buf_i = 0;
    *current_type = QUOTE_NONE;
}

void flush_token(t_segment *segments, int seg_i,
                        t_token *tokens, int *token_i)
{
    tokens[*token_i].segments = ft_calloc(seg_i + 1, sizeof(t_segment));
    ft_memcpy(tokens[*token_i].segments, segments, sizeof(t_segment) * seg_i);
    (*token_i)++;
}

void flush_segment_with_type(char *buffer, int *buf_i,
                                    t_segment *segments, int *seg_i,
                                    t_quote_type type)
{
    buffer[*buf_i] = '\0';
    segments[*seg_i].value = ft_strdup(buffer);
    segments[*seg_i].type  = type;
    (*seg_i)++;
    *buf_i = 0;
}