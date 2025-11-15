/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:54:10 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 16:54:11 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*sweep1;
	const unsigned char	*sweep2;

	sweep1 = (const unsigned char *)s1;
	sweep2 = (const unsigned char *)s2;
	while (n > 0)
	{
		if (*sweep1 != *sweep2)
			return (*sweep1 - *sweep2);
		sweep1++;
		sweep2++;
		n--;
	}
	return (0);
}
