/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:56:33 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 16:56:36 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	ch;

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
