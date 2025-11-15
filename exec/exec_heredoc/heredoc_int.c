/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:51:53 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 17:58:35 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*read_line(void)
{
	return (get_next_line(STDIN_FILENO));
}

static void	normalize_line(char *line)
{
	size_t	l;

	l = ft_strlen(line);
	if (l > 0 && line[l - 1] == '\n')
		line[l - 1] = '\0';
}

static void	write_line(const char *line, bool quoted,
						t_shenv *env, int write_fd)
{
	char	*expanded;

	if (!quoted)
	{
		expanded = expand_variables(line, env);
		if (expanded)
		{
			write(write_fd, expanded, ft_strlen(expanded));
			write(write_fd, "\n", 1);
			free(expanded);
		}
	}
	else
	{
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
	}
}

void	heredoc_interactive(t_heredoc *hdoc, t_cli *cli, int write_fd)
{
	char	*line;

	while (1)
	{
		line = read_line();
		if (!line)
			break ;
		normalize_line(line);
		if (ft_strcmp(line, hdoc->delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_line(line, hdoc->quoted, *cli->env, write_fd);
		free(line);
	}
}
