#include "libft.h"

static char	*split_strndup(const char *s, int n)
{
	char	*dup;
	int		i;

	dup = malloc (n + 1);
	i = 0;
	if (!dup)
		return (NULL);
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static int	str_count(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s != '\0' && *s != c)
				s++;
		}
	}
	return (count);
}

static void	*free_all(char **arr, int i)
{
	while (i--)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static char	**fill_split(char const *s, char c, char **res)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len > 0)
		{
			res[i] = split_strndup(s, len);
			if (!res[i++])
				return (free_all (res, i));
			s += len;
		}
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc((str_count(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (fill_split(s, c, result));
}
