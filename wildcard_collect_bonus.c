/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_collect_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 02:43:37 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcard_bonus_internal.h"

static int	should_skip(const char *name, const char *pattern)
{
	if (!name)
		return (1);
	if (ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0)
		return (1);
	if (name[0] == '.' && (!pattern || pattern[0] != '.'))
		return (1);
	return (0);
}

size_t	count_matches(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			count;

	dir = opendir(".");
	if (!dir)
		return (0);
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (!should_skip(entry->d_name, pattern)
			&& match_pattern(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

int	collect_matches(DIR *dir, const char *pattern, char **matches,
		size_t *written)
{
	struct dirent	*entry;

	*written = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (!should_skip(entry->d_name, pattern)
			&& match_pattern(pattern, entry->d_name))
		{
			matches[*written] = ft_strdup(entry->d_name);
			if (!matches[*written])
				return (-1);
			(*written)++;
		}
		entry = readdir(dir);
	}
	return (0);
}
