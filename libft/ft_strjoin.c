/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:56:58 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 16:56:59 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*comb;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	comb = (char *)malloc(len1 + len2 + 1);
	if (comb == NULL)
		return (NULL);
	ft_strlcpy(comb, s1, len1 + 1);
	ft_strlcat(comb, s2, len1 + len2 + 1);
	return (comb);
}
