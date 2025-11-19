/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:28:24 by dogs              #+#    #+#             */
/*   Updated: 2025/11/19 18:36:25 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parse_token(t_token *token, int i, t_cli *cli, int *group)
{
	
	if (token[i].value && !cli->cmd)
	{
		ft_cmd(token[i].value, cli);
		ft_args(token[i].value, cli, ft_ptr_array_len((void **)cli->args));
		cli->group = *group;
	}
	else
		ft_args(token[i].value, cli, ft_ptr_array_len((void **)cli->args));
	return (i);
}
