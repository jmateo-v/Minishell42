/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 02:44:37 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcard_bonus_internal.h"

static void	free_partial(char **matches, size_t count)
{
	size_t	index;

	index = 0;
	while (index < count)
	{
		free(matches[index]);
		index++;
	}
	free(matches);
}

static int	allocate_matches(const char *pattern, DIR **dir, char ***matches)
{
	size_t	count;

	*dir = opendir(".");
	if (!*dir)
		return (0);
	count = count_matches(pattern);
	*matches = malloc(sizeof(char *) * (count + 1));
	if (!*matches)
	{
		closedir(*dir);
		return (0);
	}
	return (1);
}

char	**expand_wildcards(const char *pattern)
{
	DIR		*dir;
	size_t	written;
	char	**matches;

	if (!allocate_matches(pattern, &dir, &matches))
		return (NULL);
	if (collect_matches(dir, pattern, matches, &written) == -1)
	{
		closedir(dir);
		free_partial(matches, written);
		return (NULL);
	}
	if (written == 0)
	{
		closedir(dir);
		free(matches);
		return (NULL);
	}
	matches[written] = NULL;
	closedir(dir);
	return (matches);
}

void	free_wildcard_matches(char **matches)
{
	size_t	index;

	if (!matches)
		return ;
	index = 0;
	while (matches[index])
	{
		free(matches[index]);
		index++;
	}
	free(matches);
}
