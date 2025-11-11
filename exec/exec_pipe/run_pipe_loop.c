/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:40:15 by dogs              #+#    #+#             */
/*   Updated: 2025/11/11 19:16:07 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	launch_child(t_cli *cmd, int prev_pipe, int *pipe_fd, bool has_next)
{
	ft_set_sig(CHILD);
	if (has_next)
		setup_child(cmd, prev_pipe, pipe_fd);
	else
		setup_child(cmd, prev_pipe, NULL);
	pipe_command(cmd);
}

static void	update_pipe_state(t_cli *cmd, bool has_next,
							int *pipe_fd, int *prev_pipe)
{
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	if (has_next)
	{
		close(pipe_fd[1]);
		*prev_pipe = pipe_fd[0];
	}
	else
		*prev_pipe = -1;
}

int	run_pipeline_loop(t_cli *cli, pid_t *pids, pid_t *last_pid)
{
	t_cli			*cur;
	t_pipe_state	s;
	pid_t			pid;
	bool			has_next;

	cur = cli;
	s.prev = -1;
	s.i = 0;
	while (cur)
	{
		has_next = (cur->next != NULL);
		if (has_next && pipe(s.p) == -1)
			exit_perror("pipe");
		pid = fork();
		if (pid == -1)
			exit_perror("fork");
		if (pid == 0)
			launch_child(cur, s.prev, s.p, has_next);
		pids[s.i++] = pid;
		update_pipe_state(cur, has_next, s.p, &s.prev);
		if (!has_next)
			*last_pid = pid;
		cur = cur->next;
	}
	return (s.i);
}
