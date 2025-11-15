/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:54:02 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 16:54:04 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*sweeper;
	const unsigned char	*buffer;

	sweeper = (unsigned char *)dest;
	buffer = (const unsigned char *)src;
	while (n > 0)
	{
		*sweeper = *buffer;
		sweeper++;
		buffer++;
		n--;
	}
	return (dest);
}
