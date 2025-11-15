/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:32:46 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 17:52:18 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	heredoc_child(t_heredoc *hdoc, t_cli *cli, int pipefd[2])
{
	ft_set_sig(CHILD);
	close(pipefd[0]);
	if (cli->s_heredoc)
		heredoc_from_string(hdoc, cli, pipefd[1]);
	else
		heredoc_interactive(hdoc, cli, pipefd[1]);
	close(pipefd[1]);
	exit(0);
}

static int	heredoc_parent(pid_t pid, t_heredoc *hdoc, int pipefd[2])
{
	int	status;

	ft_set_sig(IGNORE);
	close(pipefd[1]);
	hdoc->fd = pipefd[0];
	waitpid(pid, &status, 0);
	ft_set_sig(PARENT);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		if (WTERMSIG(status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}

int	ft_heredoc(t_heredoc *hdoc, t_cli *cli)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
		heredoc_child(hdoc, cli, pipefd);
	return (heredoc_parent(pid, hdoc, pipefd));
}
