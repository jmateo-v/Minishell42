/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:12:39 by dogs              #+#    #+#             */
/*   Updated: 2025/11/04 22:56:59 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum e_quote_state
{
    QSTATE_NONE,
    QSTATE_SINGLE,
    QSTATE_DOUBLE,
    QSTATE_ANSI_C
}
t_quote_state;
typedef enum e_seg_type
{
	QUOTE_NONE = 0,
    QUOTE_SINGLE,
    QUOTE_DOUBLE,
	QUOTE_TRANSLATION,
	QUOTE_LITERAL,
	REDIRECTION,
	OPERATOR
}	t_seg_type;
typedef enum e_token_type
{
	T_WORD = 0,
    T_REDIRECTION,
    T_OPERATOR
}	t_token_type;

typedef struct s_segment
{
    char        *value;
    t_seg_type type; 
}   t_segment;

typedef struct s_token
{
	t_segment *segments;
	char *value;
	t_seg_type seg_type;
    t_token_type token_type;
} t_token;

typedef struct s_separator_ctx
{
    t_seg_type state;
    t_seg_type current_type;
    char buffer[1024];
    int buf_i;
    int token_i;
    int seg_i;
    int len;
    int quote_state;
    t_token *tokens;
    t_segment *segments;
} t_separator_ctx;

int init_separator_ctx(t_separator_ctx *ctx, char *line);
int handle_escape_sequence(const char *line, int i, t_separator_ctx *ctx);
void add_operator_token(char c, const char *line, int *i, t_separator_ctx *ctx);
void handle_operator(char c, char *line, int *i, t_separator_ctx *ctx);
int handle_translation(const char *line, int i, t_separator_ctx *ctx);
int handle_quote_open(char c, t_separator_ctx *ctx);
void handle_quote_close(char c, t_separator_ctx *ctx);
int handle_ansi_c_quote(const char *line, int i, t_separator_ctx *ctx);
void flush_segment(t_separator_ctx *ctx);
void flush_token(t_separator_ctx *ctx);
void flush_segment_with_type(t_separator_ctx *ctx, t_seg_type type);

#endif

