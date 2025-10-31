/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:08:21 by dogs              #+#    #+#             */
/*   Updated: 2025/10/30 18:20:20 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
static t_token *clean_err_return(char *line, t_segment *segments, t_token *tokens)
{
    free(line);
    free(segments);
    ft_free_tokens(tokens);
    return NULL;
}

t_token *ft_token_sep(char *line)
{
    t_separator_ctx ctx;
    if (!init_separator_ctx(&ctx, line))
        return (NULL);

    for (int i = 0; line[i]; i++)
    {
        char c = line[i];
        if (c == '\\')
        {
            i = handle_escape_sequence(line, i, &ctx);
            continue;
        }
        if (ctx.state == QUOTE_NONE && (c == '>' || c == '<' || c == '|'))
        {
            handle_operator(c, line, &i, &ctx);
            continue;
        }       
        if (c == '$' && line[i + 1] && line[i + 1] == '"' && line[i + 2])
        {
        if (ctx.buf_i > 0)
            flush_segment(&ctx);

        int new_i = handle_translation(line, i, &ctx);
        if (new_i == -1)
            return clean_err_return(line, ctx.segments, ctx.tokens);
        i = new_i;
        continue;
        }
        if (ctx.state == QUOTE_NONE)
        {
            if (c == '\'' || c == '"') 
            {
                handle_quote_open(c, &ctx);
            } 
            else if (ft_isspace((unsigned char)c))
            {
                
                if (ctx.buf_i > 0)
                    flush_segment(&ctx);              
                if (ctx.seg_i > 0)
                {
                    flush_token(&ctx);
                    ctx.seg_i = 0;
                }
            } 
            else 
            {
                if (ctx.buf_i < (int)sizeof(ctx.buffer) - 1)
                    ctx.buffer[ctx.buf_i++] = c;
            }
        } 
        else if (ctx.state == QUOTE_SINGLE || ctx.state == QUOTE_DOUBLE)
        {
            if ((ctx.state == QUOTE_SINGLE && c == '\'') || (ctx.state == QUOTE_DOUBLE && c == '"'))
            {
                handle_quote_close(c, &ctx);
            }
            else
            {
                if (ctx.buf_i < (int)sizeof(ctx.buffer) - 1)
                    ctx.buffer[ctx.buf_i++] = c;
             }
        }
    }
    if (ctx.buf_i > 0)
        flush_segment(&ctx);
    if (ctx.seg_i > 0)
        flush_token(&ctx);
    ctx.tokens[ctx.token_i].segments = NULL;
    ctx.tokens[ctx.token_i].value = NULL;
    if (ctx.state != QUOTE_NONE)
    {
        if (ctx.state == QUOTE_SINGLE)
            write(2, "minishell: syntax error near unexpected token `''\n", 50);
        else
            write(2, "minishell: syntax error near unexpected token `\"'\n", 50);
        return clean_err_return(line, ctx.segments, ctx.tokens);
    }
    free(ctx.segments);
    free(line);
    return (ctx.tokens);
}