/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:57:52 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 16:57:53 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*finder;

	finder = NULL;
	while (*str != '\0')
	{
		if (*str == (char)c)
			finder = str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return ((char *)finder);
}
