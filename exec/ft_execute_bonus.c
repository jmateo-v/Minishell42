/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:37:18 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/10/30 18:57:41 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_bonus.h"

int	ft_execute(t_cli *cli)
{
	int	last_status;

	last_status = 0;
	expand_cli_args_wildcard(cli);
	if (!cli || !cli->cmd)
		return (perror("!cmd"), 127);
	if (has_pipes_or_redirs(cli))
		last_status = execute_pipeline(cli);
	else if (cli->is_builtin)
		last_status = execute_builtin(cli);
	else
		last_status = execute_command(cli);
	return (last_status);
}



