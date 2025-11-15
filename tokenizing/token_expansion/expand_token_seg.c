/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_seg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:36:47 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 20:33:50 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_no_segments(t_token *token, char *result)
{
	if (token->value)
		free(token->value);
	token->value = result;
	return (result);
}

static char	*expand_all_segments(t_token *token, t_cli *cli, char *result)
{
	int		s;
	char	*expanded;
	char	*tmp;

	s = 0;
	while (token->segments[s].value)
	{
		expanded = expand_segment(&token->segments[s], cli, result);
		if (!expanded)
			return (NULL);
		tmp = ft_strjoin(result, expanded);
		if (!tmp)
		{
			cleanup(result, expanded, NULL, NULL);
			return (NULL);
		}
		free(result);
		free(expanded);
		result = tmp;
		s++;
	}
	return (result);
}

char	*expand_token_segments(t_token *token, t_cli *cli)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	if (!token->segments)
		return (handle_no_segments(token, result));
	result = expand_all_segments(token, cli, result);
	if (!result)
		return (NULL);
	if (token->value)
		free(token->value);
	token->value = result;
	return (result);
}
