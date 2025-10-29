
#include "minishell.h"
#include "minishell_bonus.h"
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

static char **expand_args(char **args)
{
	int i;
	int j;
	int count;
	char **expanded;
	char **matches;

	if (!args)
		return (NULL);
	count = 0;
	for (i = 0; args[i]; i++)
	{
		if (strchr(args[i], '*'))
		{
			matches = expand_wildcards(args[i]);
			for (j = 0; matches && matches[j]; j++)
				count++;
			free_wildcard_matches(matches);
		}
		else
			count++;
	}
	expanded = malloc(sizeof(char *) * (count + 1));
	if (!expanded)
		return (NULL);
	count = 0;
	for (i = 0; args[i]; i++)
	{
		if (strchr(args[i], '*'))
		{
			matches = expand_wildcards(args[i]);
			for (j = 0; matches && matches[j]; j++)
				expanded[count++] = strdup(matches[j]);
			free_wildcard_matches(matches);
		}
		else
			expanded[count++] = strdup(args[i]);
	}
	expanded[count] = NULL;
	return (expanded);
}

void expand_cli_args_wildcard(t_cli *cli)
{
	char **expanded;

	if (!cli || !cli->args)
		return ;
	expanded = expand_args(cli->args);
	if (expanded)
	{
		ft_free_str_array(&cli->args);
		cli->args = expanded;
	}
}
