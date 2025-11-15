/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:06:01 by dogs              #+#    #+#             */
/*   Updated: 2025/11/11 18:21:54 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	should_continue_waiting(pid_t wpid)
{
	return (wpid == -1 && errno == EINTR);
}

static void	send_sigint_to_children(pid_t *pids, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		kill(pids[i], SIGINT);
		i++;
	}
}

static int	handle_exit_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		return (128 + sig);
	}
	return (1);
}

static bool	check_and_send_sigint(bool sent, pid_t *pids, int count)
{
	if (g_sig_rec && !sent)
	{
		send_sigint_to_children(pids, count);
		return (true);
	}
	return (sent);
}

int	wait_for_children(pid_t last_pid, pid_t *pids, int count)
{
	int		remaining;
	int		status;
	int		last_status;
	bool	sigint_sent;
	pid_t	wpid;

	remaining = count;
	last_status = 0;
	sigint_sent = false;
	while (remaining > 0)
	{
		wpid = waitpid(-1, &status, 0);
		if (should_continue_waiting(wpid))
			continue ;
		else if (wpid == -1)
			break ;
		remaining--;
		if (wpid == last_pid)
			last_status = status;
		sigint_sent = check_and_send_sigint(sigint_sent, pids, count);
	}
	return (handle_exit_status(last_status));
}
