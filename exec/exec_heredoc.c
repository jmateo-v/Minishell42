/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:32:46 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 15:34:16 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_prepare_heredoc_fd(t_cli *cli)
{
	int	pipefd[2];

	if (!cli->heredoc)
		return (-1);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	write(pipefd[1], cli->heredoc, ft_strlen(cli->heredoc));
	close(pipefd[1]);
	return (pipefd[0]);
}

int	ft_prepare_all_heredocs(t_cli *cli)
{
	t_cli	*current;

	current = cli;
	while (current)
	{
		if (current->heredoc)
		{
			current->heredoc_fd = ft_prepare_heredoc_fd(current);
			if (current->heredoc_fd == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
