/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:30:44 by dogs              #+#    #+#             */
/*   Updated: 2025/10/18 16:37:55 by dogs             ###   ########.fr       */
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

char *ft_esc_line(char *line, int i, int len)
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

char	*ft_escape_quotes(char *line)
{
	size_t		i;
	int		len;
	char	*esc_line;
	char	*s;

	if (!line)
		return (NULL);
	i = 0;
	s = ft_strdup(line);
	while (i < ft_strlen(s))
	{
		if (ft_strchr(QUOTES, s[i]) && (i == 0 || (i > 0 && line[i - 1] != '\\')))
		{
			len = ft_quoted_len(s + i,  s[i]);
			if (len < 0)
				return (free(s), NULL);
			esc_line = ft_esc_line(s, i , i + len);
			if (!esc_line)
				return (free(s), NULL);
			i += (len - 2);
			free(s);
			s = esc_line;
			continue ;
		}
		i++;
	}
	return (s);
}
int ft_quoted_len(char *line, char quote)
{
    
    int i = 1;
    while (line[i])
    {
        if (line[i] == quote)
        {
            if (quote == '"')
            {
                int backslash_count = 0;
                int k = i - 1;
                while (k >= 0 && line[k] == '\\')
                {
                    backslash_count++;
                    k--;
                }
                if (backslash_count % 2 == 1)
                {
                    i++;
                    continue;
                }
            }
            return i + 1;
        }
        i++;
    }
    return -1;
}


