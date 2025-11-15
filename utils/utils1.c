/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:30:44 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 23:18:11 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_escaped_line(char *line, int start, int end)
{
	char	*escaped;
	char	*t;
	char	*s;

	if (!line || start < 0 || end < start)
		return (NULL);
	if (end == 0)
		return (ft_strdup(line));
	escaped = ft_esc_str(line + start + 1, ESC_CHARS1, end - start - 2);
	t = ft_strndup(line, start);
	if (!escaped)
		return (NULL);
	s = ft_strjoin(t, escaped);
	if (!s)
		return (NULL);
	free(escaped);
	free(t);
	t = ft_strjoin(s, line + end);
	free(s);
	return (s = NULL, escaped = NULL, t);
}

char	*ft_esc_line(char *line, int i, int len)
{
	char	*esc_line;
	char	*t;

	if (ft_strchr(QUOTES, line[i]) && line[i] == line[i + 1])
	{
		t = ft_strndup(line, i);
		if (i > 0 && !t)
			return (perror("malloc1 : "), NULL);
		if (!line[i + 2])
			return (t);
		esc_line = ft_strjoin(t, line + i + 2);
		if (esc_line != t)
		{
			free(t);
			t = NULL;
		}
		if (!esc_line)
			return (perror("malloc : "), NULL);
		return (esc_line);
	}
	esc_line = ft_escaped_line(line, i, len);
	return (esc_line);
}

static int	ft_count_backslashes(char *line, int pos)
{
	int	count;

	count = 0;
	while (pos >= 0 && line[pos] == '\\')
	{
		count++;
		pos--;
	}
	return (count);
}

static int	ft_is_escaped_quote(char *line, int i, char quote)
{
	int	backslash_count;

	if (quote != '"')
		return (0);
	backslash_count = ft_count_backslashes(line, i - 1);
	if (backslash_count % 2 == 1)
		return (1);
	return (0);
}

int	ft_quoted_len(char *line, char quote)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == quote)
		{
			if (ft_is_escaped_quote(line, i, quote))
			{
				i++;
				continue ;
			}
			return (i + 1);
		}
		i++;
	}
	return (-1);
}
