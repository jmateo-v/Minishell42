/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:37:18 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/11/15 12:21:36 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_bonus.h"

static int	execute_expression(t_cli **cursor, int depth, int *last_op)
{
	int	status;
	int	op;

	status = 0;
	op = NO_OP;
	while (*cursor && (*cursor)->group >= depth)
	{
		if ((*cursor)->group > depth)
			status = execute_expression(cursor, (*cursor)->group, &op);
		else
			status = run_pipeline_group(cursor, depth, &op);
		if ((op == AND && status != 0) || (op == OR && status == 0))
		{
			skip_remaining_expression(cursor, depth);
			break ;
		}
		if (op == NO_OP)
			break ;
	}
	*last_op = op;
	return (status);
}

int	ft_execute(t_cli *cli)
{
	t_cli	*cursor;
	int		status;
	int		last_op;

	if (!cli)
		return (0);
	cursor = cli;
	status = execute_expression(&cursor, 1, &last_op);
	return (status);
}
