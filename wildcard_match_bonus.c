/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 02:44:53 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcard_bonus_internal.h"

static int	handle_star(const char *pattern, const char *str)
{
	if (*(pattern + 1) == '\0')
		return (1);
	while (*str)
	{
		if (match_pattern(pattern + 1, str))
			return (1);
		str++;
	}
	return (0);
}

static int	match_pattern_inner_loop(const char *s, const char *p)
{
	const char	*str;
	const char	*pattern;

	str = s;
	pattern = p;
	while (*pattern && *str)
	{
		if (*pattern == '*')
			return (handle_star(pattern, str));
		if (*pattern != *str)
			return (0);
		pattern++;
		str++;
	}
	return (-1);
}

int	match_pattern(const char *pattern, const char *str)
{
	int			result;
	const char	*tmp;
	const char	*seq;

	tmp = pattern;
	seq = str;
	result = match_pattern_inner_loop(seq, tmp);
	if (result != -1)
		return (result);
	while (*tmp == '*')
		tmp++;
	return (*tmp == '\0' && *seq == '\0');
}
