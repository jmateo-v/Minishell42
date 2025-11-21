/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:54:18 by dogs              #+#    #+#             */
/*   Updated: 2025/11/21 14:31:32 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H
# define ERR_LOGIC_OP "minishell: syntax error: unexpected token near "
# define ERR_PARENTHESIS "minishell: syntax error: unexpected token near "
# include <stddef.h> //TODO revisar si está permitido

typedef struct s_b_parse_ctx
{
	t_token	*tokens;
	int		len;
}			t_b_parse_ctx;

typedef struct s_cli	t_cli;

char	**expand_wildcards(const char *pattern);
void	free_wildcard_matches(char **matches);
void	expand_cli_args_wildcard(t_cli *cli);
int		handle_redir_bonus(t_b_parse_ctx *ctx, int *i, t_cli *cli);
int		process_and(t_b_parse_ctx *ctx, t_cli **cli, int *i);
int		process_or(t_b_parse_ctx *ctx, t_cli **cli, int *i);
void	skip_remaining_expression(t_cli **cursor, int depth);
int		run_pipeline_group(t_cli **cursor, int depth, int *last_op);
int		handle_redirection(char *curr, char *next);
int		handle_parenthesis_char(char *line, int i, t_separator_ctx *ctx);
int		handle_logic_operator(char *line, int i, t_separator_ctx *ctx);
int		check_logic(t_token *tokens, int n_tokens, int i);
#endif
