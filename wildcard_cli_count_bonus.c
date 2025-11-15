/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cli_count_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 02:45:16 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_bonus.h"
#include "wildcard_bonus_internal.h"

static int	count_match_entries(char **matches)
{
	int	index;

	if (!matches)
		return (0);
	index = 0;
	while (matches[index])
		index++;
	return (index);
}

int	count_expanded_items(char **args)
{
	int		count;
	int		index;
	char	**matches;

	count = 0;
	index = 0;
	while (args && args[index])
	{
		count++;
		if (ft_strchr(args[index], '*'))
		{
			matches = expand_wildcards(args[index]);
			if (matches)
			{
				count += count_match_entries(matches) - 1;
				free_wildcard_matches(matches);
			}
		}
		index++;
	}
	return (count);
}
