/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:09:21 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/11/15 16:41:45 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include <stddef.h>

typedef struct s_cli	t_cli;

typedef struct s_b_parse_ctx
{
	t_token	*tokens;
	int		len;
}		t_b_parse_ctx;

char	**expand_wildcards(const char *pattern);
void	free_wildcard_matches(char **matches);
void	expand_cli_args_wildcard(t_cli *cli);
int		handle_redir(t_b_parse_ctx *ctx, int *i, t_cli *cli);
int		process_and(t_b_parse_ctx *ctx, t_cli **cli, int *i);
int		process_or(t_b_parse_ctx *ctx, t_cli **cli, int *i);
void	skip_remaining_expression(t_cli **cursor, int depth);
int		run_pipeline_group(t_cli **cursor, int depth, int *last_op);
int		handle_redirection(char *curr, char *next);
void	expand_group_args(t_cli *start, t_cli *end);
t_cli	*find_group_end(t_cli *node, int level);

#endif
