/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cli_fill_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 16:27:58 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_bonus.h"
#include "wildcard_bonus_internal.h"

static int	duplicate_arg(const char *arg, char **expanded, int *index)
{
	expanded[*index] = ft_strdup(arg);
	if (!expanded[*index])
		return (0);
	(*index)++;
	return (1);
}

static int	copy_matches(char **matches, char **expanded, int *index)
{
	int	match_index;

	match_index = 0;
	while (matches[match_index])
	{
		expanded[*index] = ft_strdup(matches[match_index]);
		if (!expanded[*index])
			return (0);
		(*index)++;
		match_index++;
	}
	return (1);
}

static int	append_wildcard_matches(const char *arg, char **expanded,
		int *index)
{
	char	**matches;
	int		status;

	matches = expand_wildcards(arg);
	if (!matches)
		return (duplicate_arg(arg, expanded, index));
	status = copy_matches(matches, expanded, index);
	free_wildcard_matches(matches);
	if (!status)
		return (0);
	return (1);
}

int	fill_expanded_items(char **args, char **expanded, int *index)
{
	int	arg_index;

	arg_index = 0;
	while (args && args[arg_index])
	{
		if (!ft_strchr(args[arg_index], '*'))
		{
			if (!duplicate_arg(args[arg_index], expanded, index))
				return (0);
		}
		else if (!append_wildcard_matches(args[arg_index], expanded, index))
			return (0);
		arg_index++;
	}
	return (1);
}

void	free_partial_args(char **expanded, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		free(expanded[index]);
		index++;
	}
	free(expanded);
}
