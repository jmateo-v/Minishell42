/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_helpers_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:37:18 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/11/15 16:41:28 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_bonus.h"

t_cli	*find_group_end(t_cli *node, int level)
{
	t_cli	*end;

	end = node;
	while (end && end->op == PIPE && end->next && end->next->group >= level)
		end = end->next;
	return (end);
}

void	expand_group_args(t_cli *start, t_cli *end)
{
	t_cli	*node;

	node = start;
	while (node)
	{
		expand_cli_args_wildcard(node);
		if (node == end)
			break ;
		node = node->next;
	}
}

int	exec_group(t_cli *start, t_cli *end, t_cli *next)
{
	int	status;

	if (has_pipes_or_redirs(start) || start->op == PIPE)
	{
		end->next = NULL;
		status = execute_pipeline(start);
		end->next = next;
	}
	else if (start->is_builtin)
		status = execute_builtin(start);
	else
		status = execute_command(start);
	return (status);
}

int	run_pipeline_group(t_cli **cursor, int depth, int *last_op)
{
	t_cli	*start;
	t_cli	*end;
	t_cli	*next;
	int		status;

	start = *cursor;
	end = find_group_end(start, depth);
	next = end->next;
	//expand_group_args(start, end);
	if (!start->cmd)
	{
		*cursor = next;
		*last_op = end->op;
		return (127);
	}
	status = exec_group(start, end, next);
	*last_op = end->op;
	*cursor = next;
	return (status);
}

void	skip_remaining_expression(t_cli **cursor, int depth)
{
	t_cli	*node;
	t_cli	*end;

	while (*cursor && (*cursor)->group >= depth)
	{
		node = *cursor;
		if (node->group > depth)
		{
			skip_remaining_expression(cursor, node->group);
			continue ;
		}
		end = find_group_end(node, depth);
		*cursor = end->next;
	}
}
