/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:48:03 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/10/06 13:50:10 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*gnl_strchr(const char *str, int c)
{
	unsigned char	ch;

	if (!str)
		return (NULL);
	ch = (unsigned char)c;
	while (*str != '\0')
	{
		if ((unsigned char)*str == ch)
			return ((char *)str);
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (NULL);
}

char	*gnl_strdup(const char *str)
{
	size_t	len;
	size_t	i;
	char	*dup;

	if (!str)
		return (NULL);
	len = gnl_strlen(str);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	gnl_strlen(const char *c)
{
	size_t	i;

	if (!c)
		return (0);
	i = 0;
	while (c[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	copy_str(char *dest, char *src, size_t *index)
{
	size_t	i;

	i = 0;
	if (!src)
		return ;
	while (src[i])
	{
		dest[*index] = src[i];
		i++;
		(*index)++;
	}
}

char	*gnl_strjoin(char *s1, char const *s2)
{
	size_t	i;
	char	*comb;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (gnl_strdup(s2));
	comb = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (comb == NULL)
		return (NULL);
	i = 0;
	copy_str(comb, s1, &i);
	copy_str(comb, (char *)s2, &i);
	comb[i] = '\0';
	free(s1);
	return (comb);
}
