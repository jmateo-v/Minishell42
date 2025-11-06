/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:58:06 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 16:58:07 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*temp;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	temp = sub;
	while (s[start] != '\0' && len > 0)
	{
		*temp = s[start];
		temp++;
		start++;
		len--;
	}
	*temp = '\0';
	return (sub);
}
