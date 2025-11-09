
#include "minishell.h"
#include "minishell_bonus.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

static int	match_pattern(const char *pattern, const char *str);

int	match_pattern_inner_loop(const char *s, const char *p)
{
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
			return (0);
	}
	return (-1);
}

static int	match_pattern(const char *pattern, const char *str)
{
	int			ret;
	const char	*p;
	const char	*s;

	p = pattern;
	s = str;
	ret = match_pattern_inner_loop(s, p);
	if (ret != -1)
		return (ret);
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
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_pattern(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

size_t	expand_wildcards_inner_loop(struct dirent *entry, DIR *dir,
		const char *pattern, char **matches)
{
	size_t			k;
	size_t			ret;

	ret = 0;
	while (entry != NULL)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(pattern, entry->d_name))
		{
			matches[ret] = strdup(entry->d_name);
			if (!matches[ret])
			{
				k = 0;
				while (k < ret)
				{
					free(matches[k]);
					k++;
				}
				free(matches);
				closedir(dir);
				return (0);
			}
			ret++;
		}
		entry = readdir(dir);
	}
	return (ret);
}

char	**expand_wildcards(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			count;
	char			**matches;
	size_t			i;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	count = count_matches(pattern);
	matches = malloc(sizeof(char *) * (count + 1));
	if (!matches)
	{
		closedir(dir);
		return (NULL);
	}
	entry = readdir(dir);
	i = expand_wildcards_inner_loop(entry, dir, pattern, matches);
	if (i == 0)
	{
		free(matches);
		closedir(dir);
		return (NULL);
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

static char	**expand_args(char **args)
{
	int		i;
	int		j;
	int		count;
	char	**expanded;
	char	**matches;

	if (!args)
		return (NULL);
	count = 0;
	i = 0;
	while (args[i])
	{
		if (strchr(args[i], '*'))
		{
			matches = expand_wildcards(args[i]);
			if (matches)
			{
				j = 0;
				while (matches[j])
				{
					count++;
					j++;
				}
				free_wildcard_matches(matches);
			}
			else
				count++;
		}
		else
			count++;
		i++;
	}
	expanded = malloc(sizeof(char *) * (count + 1));
	if (!expanded)
		return (NULL);
	count = 0;
	i = 0;
	while (args[i])
	{
		if (strchr(args[i], '*'))
		{
			matches = expand_wildcards(args[i]);
			if (matches)
			{
				j = 0;
				while (matches[j])
				{
					expanded[count++] = strdup(matches[j]);
					j++;
				}
				free_wildcard_matches(matches);
			}
			else
				expanded[count++] = strdup(args[i]);
		}
		else
			expanded[count++] = strdup(args[i]);
		i++;
	}
	expanded[count] = NULL;
	return (expanded);
}

void	expand_cli_args_wildcard(t_cli *cli)
{
	char	**expanded;

	if (!cli || !cli->args)
		return ;
	expanded = expand_args(cli->args);
	if (expanded)
	{
		ft_free_str_array(&cli->args);
		cli->args = expanded;
	}
}
