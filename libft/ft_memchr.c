/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:55:35 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 16:55:36 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*sweeper;

	sweeper = (unsigned char *)s;
	while (n > 0)
	{
		if (*sweeper == (unsigned char)c)
			return ((void *)sweeper);
		sweeper++;
		n--;
	}
	return (NULL);
}
