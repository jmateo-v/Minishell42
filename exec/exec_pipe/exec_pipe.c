/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:21:28 by dogs              #+#    #+#             */
/*   Updated: 2025/11/11 18:50:08 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_perror(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static int	count_commands(t_cli *cli)
{
	int		count;
	t_cli	*tmp;

	count = 0;
	tmp = cli;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static pid_t	*allocate_child_pids(int num_cmds)
{
	pid_t	*pids;

	pids = calloc(num_cmds, sizeof(pid_t));
	if (!pids)
		return (perror("calloc"), NULL);
	return (pids);
}

int	execute_pipeline(t_cli *cli)
{
	pid_t	*child_pids;
	pid_t	last_pid;
	int		num_cmds;
	int		child_count;
	int		exit_code;

	num_cmds = count_commands(cli);
	child_pids = allocate_child_pids(num_cmds);
	if (!child_pids)
		return (1);
	ft_set_sig(IGNORE);
	if (ft_prepare_all_heredocs(cli) == -1)
		return (1);
	child_count = run_pipeline_loop(cli, child_pids, &last_pid);
	ft_set_sig(IGNORE);
	exit_code = wait_for_children(last_pid, child_pids, child_count);
	ft_set_sig(PARENT);
	free(child_pids);
	return (exit_code);
}
