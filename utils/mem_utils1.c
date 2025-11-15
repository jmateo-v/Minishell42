/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:04:40 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 23:05:05 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_segments(t_segment *segs)
{
	int	j;

	if (!segs)
		return ;
	j = 0;
	while (segs[j].value != NULL)
	{
		free(segs[j].value);
		j++;
	}
	free(segs);
}

void	ft_free_tokens(t_token *tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (1)
	{
		if (tokens[i].segments == NULL && tokens[i].value == NULL)
			break ;
		if (tokens[i].value)
			free(tokens[i].value);
		free_segments(tokens[i].segments);
		i++;
	}
	free(tokens);
}
