/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_finalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:19:33 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 18:55:24 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	total_segments_len(t_segment *segments)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (segments[i].value)
	{
		len += (int)ft_strlen(segments[i].value);
		i++;
	}
	return (len);
}

static void	concat_segments(char *dst, t_segment *segments)
{
	int		i;
	char	*p;
	size_t	l;

	i = 0;
	p = dst;
	while (segments[i].value)
	{
		l = ft_strlen(segments[i].value);
		ft_memcpy(p, segments[i].value, l);
		p += l;
		i++;
	}
	*p = '\0';
}

int	ft_token_finalize(t_token *tok)
{
	int		total_len;
	char	*res;

	if (!tok || !tok->segments || !tok->segments[0].value)
		return (0);
	total_len = total_segments_len(tok->segments);
	res = malloc(total_len + 1);
	if (!res)
		return (0);
	concat_segments(res, tok->segments);
	tok->value = res;
	tok->seg_type = tok->segments[0].type;
	return (1);
}

void	ft_finalize_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].segments)
	{
		if (!tokens[i].value)
			ft_token_finalize(&tokens[i]);
		i++;
	}
}
