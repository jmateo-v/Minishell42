/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:00:00 by dansanc3          #+#    #+#             */
/*   Updated: 2025/10/23 19:57:18 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **expand_args(char **args)
{
	int i, j, count = 0;
	char **expanded = NULL;
	char **matches;
	for (i = 0; args[i]; i++)
	{
		if (strchr(args[i], '*'))
		{
			matches = expand_wildcards(args[i]);
			for (j = 0; matches && matches[j]; j++)
				count++;
			free_wildcard_matches(matches);
		}
		else
			count++;
	}
	expanded = malloc(sizeof(char *) * (count + 1));
	if (!expanded)
		return NULL;
	count = 0;
	for (i = 0; args[i]; i++)
	{
		if (strchr(args[i], '*'))
		{
			matches = expand_wildcards(args[i]);
			for (j = 0; matches && matches[j]; j++)
				expanded[count++] = strdup(matches[j]);
			free_wildcard_matches(matches);
		}
		else
			expanded[count++] = strdup(args[i]);
	}
	expanded[count] = NULL;
	return expanded;
}

void expand_cli_args_wildcard(t_cli *cli)
{
    char **expanded;
    if (!cli || !cli->args)
        return;
    expanded = expand_args(cli->args);
    if (expanded)
    {
        ft_free_str_array(&cli->args);
        cli->args = expanded;
    }
}
