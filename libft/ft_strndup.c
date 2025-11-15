/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 09:58:44 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 10:00:32 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;

	if (!src)
		return (NULL);
	dest = (char *)ft_calloc(n + 1, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, n + 1);
	return (dest);
}
