#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include <stddef.h> //TODO revisar si está permitido

typedef struct s_cli t_cli;

char	**expand_wildcards(const char *pattern);
void	free_wildcard_matches(char **matches);
void	expand_cli_args_wildcard(t_cli *cli);

#endif
