/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:21:56 by dogs              #+#    #+#             */
/*   Updated: 2025/10/17 12:25:50 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_precount_tokens(const char *line)
{
	int i;
	int count;
	int len;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break;
		if (ft_strchr(QUOTES, line[i]))
		{
			len = ft_quoted_len((char *)&line[i], line[i]);
			if (len < 0)
				return (-1);
			i += len;
		}
		else
		{
			while (line[i] && !ft_isspace(line[i]) && !ft_strchr(QUOTES, line[i]))
				i++;
		}
		count++;
	}
	return (count);
}

char	*ft_trim_spaces(char *line)
{
	size_t		i;
	int		j;
	char	sep;
	char	*trimmed;

	i = 0;
	if (ft_trim_s_len(line) < 0)
		return (NULL);
	trimmed = ft_calloc(ft_trim_s_len(line) + 1, sizeof(char));
	j = 0;
	while (trimmed && line && i < ft_strlen(line))
	{
		while (ft_isspace(line[i]) && (ft_isspace(line[i + 1]) || !line[i + 1]))
			i++;
		if (i < ft_strlen(line) && ft_strchr(QUOTES, line[i]) && (i == 0 || (i > 0 && line[i - 1] != '\\')))
		{
			sep = line[i];
			trimmed[j++] = line[i++];
			while (i < ft_strlen(line) && line[i] != sep)
				trimmed[j++] = line[i++];
		}
		if (i < ft_strlen(line))
			trimmed[j++] = line[i++];
	}
	return (trimmed);
}