#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include <stddef.h> //TODO revisar si está permitido

typedef struct s_b_parse_ctx
{
	t_token	*tokens;
	int		len;
}			t_b_parse_ctx;

typedef struct s_cli t_cli;

char	**expand_wildcards(const char *pattern);
void	free_wildcard_matches(char **matches);
void	expand_cli_args_wildcard(t_cli *cli);
int		handle_redir_bonus(t_b_parse_ctx *ctx, int *i, t_cli *cli);
int	process_and(t_b_parse_ctx *ctx, t_cli **cli, int *i);
int	process_or(t_b_parse_ctx *ctx, t_cli **cli, int *i);
void	skip_remaining_expression(t_cli **cursor, int depth);
int	run_pipeline_group(t_cli **cursor, int depth, int *last_op);
int	handle_redirection(char *curr, char *next);
int handle_parenthesis_char(char *line, int i, t_separator_ctx *ctx);
#endif
