/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:15:45 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 23:17:19 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_is_unescaped_quote(char *s, size_t i, char *line)
{
	if (ft_strchr(QUOTES, s[i]))
	{
		if (i == 0 || (i > 0 && line[i - 1] != '\\'))
			return (1);
	}
	return (0);
}

static char	*ft_handle_escape(char *s, size_t *i)
{
	int		len;
	char	*esc_line;

	len = ft_quoted_len(s + *i, s[*i]);
	if (len < 0)
		return (free(s), NULL);
	esc_line = ft_esc_line(s, *i, *i + len);
	if (!esc_line)
		return (free(s), NULL);
	*i += (len - 2);
	free(s);
	return (esc_line);
}

char	*ft_escape_quotes(char *line)
{
	size_t	i;
	char	*s;
	char	*esc_line;

	if (!line)
		return (NULL);
	i = 0;
	s = ft_strdup(line);
	while (i < ft_strlen(s))
	{
		if (ft_is_unescaped_quote(s, i, line))
		{
			esc_line = ft_handle_escape(s, &i);
			if (!esc_line)
				return (NULL);
			s = esc_line;
			continue ;
		}
		i++;
	}
	return (s);
}
