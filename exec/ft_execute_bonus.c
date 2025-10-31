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

/* debug helper removed */

int	ft_execute(t_cli *cli)
{
	int	last_status;

	last_status = 0;
	if (!cli || !cli->cmd)
		return (perror("!cmd"), 127);
	expand_cli_args_wildcard(cli);
	while (cli)
	{
		t_cli *group_end;
		t_cli *next_group;
		int status;

		/* find end of pipeline group starting at cli */
		group_end = cli;
		while (group_end->op == PIPE && group_end->next)
			group_end = group_end->next;
		next_group = group_end->next;

		/* execute pipeline if present, else single command */
		if (has_pipes_or_redirs(cli) || cli->op == PIPE)
		{
			/* temporarily cut the list so execute_pipeline handles only the group */
			group_end->next = NULL;
			status = execute_pipeline(cli);
			group_end->next = next_group;
			last_status = status;
		}
		else
		{
			if (cli->is_builtin)
				status = execute_builtin(cli);
			else
				status = execute_command(cli);
			last_status = status;
		}

		/* decide whether to execute next_group depending on logical operators */
		if (!next_group)
			break;
		if (group_end->op == AND && last_status != 0)
		{
			/* skip next_group */
			t_cli *skip_end = next_group;
			while (skip_end->op == PIPE && skip_end->next)
				skip_end = skip_end->next;
			cli = skip_end->next;
			continue;
		}
		if (group_end->op == OR && last_status == 0)
		{
			t_cli *skip_end = next_group;
			while (skip_end->op == PIPE && skip_end->next)
				skip_end = skip_end->next;
			cli = skip_end->next;
			continue;
		}
		cli = next_group;
	}
	return (last_status);
}



