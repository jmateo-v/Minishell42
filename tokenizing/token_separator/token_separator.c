/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:08:21 by dogs              #+#    #+#             */
/*   Updated: 2025/11/04 22:56:31 by dogs             ###   ########.fr       */
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
        return NULL;

    int i = 0;
    while (line[i])
    {
        char c = line[i];
        //printf("CHAR: '%c', quote_state=%d, buf='%.*s'\n", c, ctx.quote_state, ctx.buf_i, ctx.buffer);

        if (ctx.quote_state == QSTATE_NONE && c == '\\')
        {
            i = handle_escape_sequence(line, i, &ctx);
            if (i < 0) return clean_err_return(line, ctx.segments, ctx.tokens);
            continue;
        }

        if (ctx.quote_state == QSTATE_NONE && (c == '>' || c == '<' || c == '|'))
        {
            handle_operator(c, line, &i, &ctx);
            i++;
            continue;
        }

        if (ctx.quote_state == QSTATE_NONE && c == '$' && line[i+1] == '"' && line[i+2])
        {
            if (ctx.buf_i > 0) flush_segment_with_type(&ctx, QUOTE_NONE);
            int new_i = handle_translation(line, i, &ctx);
            if (new_i == -1) return clean_err_return(line, ctx.segments, ctx.tokens);
            i = new_i + 1;
            continue;
        }

        if (ctx.quote_state == QSTATE_NONE && c == '$' && line[i+1] == '\'' && line[i+2])
        {
            if (ctx.buf_i > 0) flush_segment_with_type(&ctx, QUOTE_NONE);
            int new_i = handle_ansi_c_quote(line, i, &ctx);
            if (new_i == -1) return clean_err_return(line, ctx.segments, ctx.tokens);
            i = new_i + 1;
            continue;
        }

        if (ctx.quote_state == QSTATE_NONE) 
        {
            if (c == '\'')
            {
                if (ctx.buf_i > 0)
                    flush_segment_with_type(&ctx, QUOTE_NONE);
                ctx.quote_state = QSTATE_SINGLE;
                i++;
                continue;
            }
            else if (c == '"') 
            {
                if (ctx.buf_i > 0)
                    flush_segment_with_type(&ctx, QUOTE_NONE);
                ctx.quote_state = QSTATE_DOUBLE;
                i++;
                continue;
            } 
            else if (ft_isspace((unsigned char)c))
            {
            if (ctx.buf_i > 0)
                flush_segment_with_type(&ctx, QUOTE_NONE);
            if (ctx.seg_i > 0 || ctx.buf_i > 0)
            {
                flush_token(&ctx); 
                ctx.seg_i = 0; 
            }
                i++;
                continue;
            }
           
            else
            {
                if (ctx.buf_i < (int)sizeof(ctx.buffer) - 1)
                    ctx.buffer[ctx.buf_i++] = c;
                i++;
                continue;
            }
        } 
        else if (ctx.quote_state == QSTATE_SINGLE)
        {
            if (c == '\'') 
            {
                ctx.quote_state = QSTATE_NONE;
                flush_segment_with_type(&ctx, QUOTE_SINGLE);
                i++;
                continue;
            } 
            else 
            {
                if (ctx.buf_i < (int)sizeof(ctx.buffer) - 1)
                    ctx.buffer[ctx.buf_i++] = c;
                i++;
                continue;
            }
        } 
        else if (ctx.quote_state == QSTATE_DOUBLE) 
        {
            if (c == '"')
            {  
                flush_segment_with_type(&ctx, QUOTE_DOUBLE);
                ctx.quote_state = QSTATE_NONE;
                
                i++;
                continue;
            }
            else 
            {
                if (ctx.buf_i < (int)sizeof(ctx.buffer) - 1)
                    ctx.buffer[ctx.buf_i++] = c;
                i++;
                continue;
            }
        }
    }

    if (ctx.buf_i > 0)
        flush_segment_with_type(&ctx, QUOTE_NONE);
    if (ctx.seg_i > 0)
        flush_token(&ctx);

    ctx.tokens[ctx.token_i].segments = NULL;
    ctx.tokens[ctx.token_i].value = NULL;

    if (ctx.quote_state != QSTATE_NONE)
    {
        if (ctx.quote_state == QSTATE_SINGLE)
            write(2, "minishell: syntax error near unexpected token `''\n", 50);
        else
            write(2, "minishell: syntax error near unexpected token `\"'\n", 50);
        return clean_err_return(line, ctx.segments, ctx.tokens);
    }

    free(ctx.segments);
    free(line);
    return ctx.tokens;
}
