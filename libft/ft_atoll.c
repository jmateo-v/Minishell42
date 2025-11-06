/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:35:07 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 15:40:22 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static const char	*skip_whitespace(const char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	return (str);
}

static int	get_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static unsigned long long	parse_number(const char **str, int *overflow)
{
	unsigned long long	tmp;
	int					digit;

	tmp = 0;
	*overflow = 0;
	while (**str && ft_isdigit(**str))
	{
		digit = **str - '0';
		if (tmp > (ULLONG_MAX - digit) / 10)
		{
			*overflow = 1;
			return (tmp);
		}
		tmp = tmp * 10 + digit;
		(*str)++;
	}
	return (tmp);
}

long long	ft_atoll(const char *str)
{
	long long			result;
	int					sign;
	int					overflow;
	unsigned long long	tmp;

	str = skip_whitespace(str);
	sign = get_sign(&str);
	tmp = parse_number(&str, &overflow);
	if (overflow)
	{
		if (sign == 1)
			return (LLONG_MAX);
		else
			return (LLONG_MIN);
	}
	result = (long long)(tmp * sign);
	return (result);
}
