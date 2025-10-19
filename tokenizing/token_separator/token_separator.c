/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:08:21 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 10:56:27 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
static t_token *clean_err_return(t_segment *segments, t_token *tokens)
{
    free(segments);
    ft_free_tokens(tokens);
    return NULL;
}

t_token *ft_token_sep(char *line)
{
    t_quote_type state = QUOTE_NONE;
    t_quote_type current_type = QUOTE_NONE;
    int len = ft_strlen(line);
    char buffer[1024];
    int buf_i = 0;
    int token_i = 0;
    t_token *tokens = ft_calloc(len + 1, sizeof(t_token));
    t_segment *segments = ft_calloc(len + 1, sizeof(t_segment));
    int seg_i = 0;

    if (!line || !tokens || !segments)
        return NULL;
    for (int i = 0; line[i]; i++)
    {
        char c = line[i];
        if (c == '\\')
        {
            i = handle_escape_sequence(line, i, buffer, &buf_i, state, &current_type);
            continue;
        }
        if (state == QUOTE_NONE && (c == '>' || c == '<' || c == '|'))
        {
            handle_operator(c, line, &i, buffer, &buf_i, segments, &seg_i,
                    &current_type, tokens, &token_i);
            continue;
        }       
        if (c == '$' && line[i + 1] && line[i + 1] == '"' && line[i + 2])
        {
        if (buf_i > 0)
            flush_segment(buffer, &buf_i, segments, &seg_i, &current_type);

        int new_i = handle_translation(line, i, buffer, &buf_i, segments, &seg_i);
        if (new_i == -1)
            return clean_err_return(segments, tokens);
        i = new_i;
        continue;
        }
        if (state == QUOTE_NONE)
        {
            if (c == '\'' || c == '"') 
            {
                handle_quote_open(c, buffer, &buf_i, segments, &seg_i,
                          &current_type, &state);
            } 
            else if (ft_isspace((unsigned char)c))
            {
                
                if (buf_i > 0)
                    flush_segment(buffer, &buf_i, segments, &seg_i, &current_type);
                
                if (seg_i > 0)
                {
                    flush_token(segments, seg_i, tokens, &token_i);
                    seg_i = 0;
                }
            } 
            else 
            {
                if (buf_i < (int)sizeof(buffer) - 1)
                    buffer[buf_i++] = c;
            }
        } 
        else if (state == QUOTE_SINGLE || state == QUOTE_DOUBLE)
        {
            if ((state == QUOTE_SINGLE && c == '\'') ||
                (state == QUOTE_DOUBLE && c == '"'))
            {
                handle_quote_close(c, buffer, &buf_i, segments, &seg_i,
                           &current_type, &state);
            }
            else
            {
                if (buf_i < (int)sizeof(buffer) - 1)
                    buffer[buf_i++] = c;
             }
        }
    }
    if (buf_i > 0)
        flush_segment(buffer, &buf_i, segments, &seg_i, &current_type);
    if (seg_i > 0)
        flush_token(segments, seg_i, tokens, &token_i);
    tokens[token_i].segments = NULL;
    tokens[token_i].value = NULL;

    #include <unistd.h>

    if (state != QUOTE_NONE)
    {
        if (state == QUOTE_SINGLE)
            write(2, "minishell: syntax error near unexpected token `''\n", 50);
        else
            write(2, "minishell: syntax error near unexpected token `\"'\n", 50);
        return clean_err_return(segments, tokens);
    }
    free(segments);
    free(line);
    return tokens;
}