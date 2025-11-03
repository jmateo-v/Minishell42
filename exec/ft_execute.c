/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:37:18 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/11/02 22:08:22 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../include/minishell_bonus.h"

int	ft_execute(t_cli *cli)
{
	int	last_status;
    last_status = 0;
    if (!cli || !cli->cmd)
        return (127);
    if (has_pipes_or_redirs(cli))
        last_status = execute_pipeline(cli);
    else if (cli->is_builtin)
        last_status = execute_builtin(cli);
    else
        last_status = execute_command(cli);
    return (last_status);
}



