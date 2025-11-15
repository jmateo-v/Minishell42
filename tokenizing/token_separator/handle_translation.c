/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:48:43 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 19:07:15 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_translation(const char *line, int i, t_separator_ctx *ctx)
{
	i += 2;
	while (line[i] && line[i] != '"')
	{
		if (ctx->buf_i < (int) sizeof(ctx->buffer) - 1)
			ctx->buffer[ctx->buf_i++] = line[i];
		i++;
	}
	if (line[i] != '"')
	{
		ft_perror("\"", SYN_ERR);
		return (-1);
	}
	return (i);
}
