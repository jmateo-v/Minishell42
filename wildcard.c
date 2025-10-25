

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

static int	match_pattern(const char *pattern, const char *str)
{
	const char	*p = pattern;
	const char	*s = str;

	while (*p && *s)
	{
		if (*p == '*')
		{
			if (!*(p + 1))
				return (1);
			while (*s)
			{
				if (match_pattern(p + 1, s))
					return (1);
				s++;
			}
			return (0);
		}
		else if (*p == *s)
		{
			p++;
			s++;
		}
		else
		{
			return (0);
		}
	}
	while (*p == '*')
		p++;
	return (!*p && !*s);
}

static	size_t	count_matches(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	while ((entry = readdir(dir)))
	{
		if (match_pattern(pattern, entry->d_name))
			count++;
	}
	closedir(dir);
	return (count);
}

char	**expand_wildcards(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			count;
	char			**matches;
	size_t			i;

	dir = opendir(".");
	count = count_matches(pattern);
	matches = malloc(sizeof(char *) * (count + 1));
	i = 0;
	if (!dir || !matches)
		return (NULL);
	while ((entry = readdir(dir)))
	{
		if (match_pattern(pattern, entry->d_name))
		{
			matches[i] = strdup(entry->d_name); 
			i++;
		}
	}
	matches[i] = NULL;
	closedir(dir);
	return (matches);
}

void	free_wildcard_matches(char **matches)
{
	size_t	i;

	i = 0;
	if (!matches)
		return ;
	while (matches[i])
	{
		free(matches[i]);
		i++;
	}
	free(matches);
}
