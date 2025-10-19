/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:48:43 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 10:39:46 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handle_translation(const char *line, int i,
                       char *buffer, int *buf_i,
                       t_segment *segments, int *seg_i)
{
    i += 2;

    while (line[i] && line[i] != '"') 
    {
        if (*buf_i < (int)sizeof(buffer) - 1)
            buffer[(*buf_i)++] = line[i++];
    }

    if (line[i] != '"') 
    {
        write(2, "minishell: syntax error near unexpected token `\"'\n", 
            ft_strlen("minishell: syntax error near unexpected token `\"'\n"));
        return (-1);
    }

    buffer[*buf_i] = '\0';
    segments[*seg_i].value = ft_strdup(buffer);
    segments[*seg_i].type = QUOTE_TRANSLATION;
    (*seg_i)++;
    *buf_i = 0;

    return i;
}
