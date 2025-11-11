/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:54:54 by dogs              #+#    #+#             */
/*   Updated: 2025/11/11 18:26:28 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	setup_input(t_cli *cmd, int prev_pipe)
{
	int	fd;

	if (cmd->heredoc_fd != -1)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
	else if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			exit_perror(cmd->infile);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
}

static void	setup_output(t_cli *cmd, int *pipe_fd)
{
	int	fd;
	int	flags;

	if (cmd->outfile)
	{
		flags = O_WRONLY | O_CREAT;
		if (cmd->r_mode == WRITE)
			flags |= O_TRUNC;
		else if (cmd->r_mode == APPEND)
			flags |= O_APPEND;
		fd = open(cmd->outfile, flags, 0644);
		if (fd < 0)
			exit_perror(cmd->outfile);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (pipe_fd)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

static void	close_unused_fds(int prev_pipe, int *pipe_fd)
{
	if (prev_pipe != -1)
		close(prev_pipe);
	if (pipe_fd && pipe_fd[0] != -1)
		close(pipe_fd[0]);
}

void	setup_child(t_cli *cmd, int prev_pipe, int *pipe_fd)
{
	setup_input(cmd, prev_pipe);
	setup_output(cmd, pipe_fd);
	close_unused_fds(prev_pipe, pipe_fd);
}
