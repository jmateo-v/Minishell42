/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:28:24 by dogs              #+#    #+#             */
/*   Updated: 2025/11/21 11:55:16 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parse_token(t_token *token, int i, t_cli *cli, int *group)
{
	if (token[i].token_type == T_OP_BRACKETS
		|| token[i].token_type == T_CL_BRACKETS)
		return (i);
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
