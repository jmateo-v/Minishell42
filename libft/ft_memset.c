/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:53:42 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 16:53:44 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*sweeper;

	sweeper = (unsigned char *)s;
	while (n > 0)
	{
		*sweeper = (unsigned char)c;
		sweeper++;
		n--;
	}
	return (s);
}
