/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus_internal.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:09:33 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/11/15 15:11:49 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_INTERNAL_H
# define WILDCARD_BONUS_INTERNAL_H

# include <dirent.h>
# include <stddef.h>

int		match_pattern(const char *pattern, const char *str);
size_t	count_matches(const char *pattern);
int		collect_matches(DIR *dir, const char *pattern, char **matches,
			size_t *written);
int		count_expanded_items(char **args);
int		fill_expanded_items(char **args, char **expanded, int *index);
void	free_partial_args(char **expanded, int count);

#endif
