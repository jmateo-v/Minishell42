#ifndef WILDCARD_BONUS_INTERNAL_H
# define WILDCARD_BONUS_INTERNAL_H

# include <dirent.h>
# include <stddef.h>

int	match_pattern(const char *pattern, const char *str);
size_t	count_matches(const char *pattern);
int	collect_matches(DIR *dir, const char *pattern, char **matches,
		size_t *written);
int	count_expanded_items(char **args);
int	fill_expanded_items(char **args, char **expanded, int *index);
void	free_partial_args(char **expanded, int count);

#endif
