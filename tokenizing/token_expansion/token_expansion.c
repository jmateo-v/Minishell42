/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:11:57 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 19:45:07 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_expand_tokens(t_token *tokens, int *len, t_cli *cli)
{
	int	i;

	if (!tokens || !len || *len <= 0 || !cli)
		return (NULL);
	i = 0;
	while (i < *len)
	{
		if (!expand_token_segments(&tokens[i], cli))
			return (NULL);
		i++;
	}
	return (tokens);
}
