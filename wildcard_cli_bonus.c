/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cli_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 02:45:29 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_bonus.h"
#include "wildcard_bonus_internal.h"

static char	**build_expanded_args(char **args)
{
	char	**expanded;
	int		count;
	int		index;

	count = count_expanded_items(args);
	expanded = malloc(sizeof(char *) * (count + 1));
	if (!expanded)
		return (NULL);
	index = 0;
	if (!fill_expanded_items(args, expanded, &index))
	{
		free_partial_args(expanded, index);
		return (NULL);
	}
	expanded[index] = NULL;
	return (expanded);
}

void	expand_cli_args_wildcard(t_cli *cli)
{
	char	**expanded;

	if (!cli || !cli->args)
		return ;
	expanded = build_expanded_args(cli->args);
	if (!expanded)
		return ;
	ft_free_str_array(&cli->args);
	cli->args = expanded;
}
