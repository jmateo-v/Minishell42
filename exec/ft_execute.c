/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:37:18 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/11/14 17:46:06 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_heredoc_expansion(t_cli *cli)
{
	char	*expanded;

	if (!isatty(STDIN_FILENO) && cli->s_heredoc)
	{
		if (cli->heredocs->quoted == false)
		{
			expanded = expand_variables(cli->s_heredoc, *cli->env);
			if (expanded)
			{
				free(cli->s_heredoc);
				cli->s_heredoc = expanded;
			}
			else
				return (perror("ft_realloc"), 1);
		}
	}
	return (0);
}

static int	process_heredocs(t_cli *cli)
{
	int	i;
	int	status;

	i = 0;
	while (i < cli->num_heredocs)
	{
		status = ft_heredoc(&cli->heredocs[i], cli);
		if (status != 0)
			return (status);
		i++;
	}
	return (0);
}

static int	execute_cli_command(t_cli *cli)
{
	if (!cli->cmd)
	{
		if (cli->num_heredocs > 0)
			return (0);
		return (127);
	}
	if (has_pipes_or_redirs(cli))
		return (execute_pipeline(cli));
	else if (cli->is_builtin)
		return (execute_builtin(cli));
	else
		return (execute_command(cli));
}

int	ft_execute(t_cli *cli)
{
	int	status;

	if (!cli)
		return (127);
	status = handle_heredoc_expansion(cli);
	if (status != 0)
		return (status);
	if (cli->num_heredocs > 0)
	{
		status = process_heredocs(cli);
		if (status != 0)
			return (status);
	}
	return (execute_cli_command(cli));
}
