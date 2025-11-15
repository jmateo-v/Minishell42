/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_script.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:50:45 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 18:04:05 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*extract_heredoc_line(const char *p, const char *nl)
{
	size_t	len;
	char	*line;

	if (nl)
		len = (size_t)(nl - p);
	else
		len = ft_strlen(p);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, p, len);
	line[len] = '\0';
	return (line);
}

static bool	is_delimiter(const char *line, const char *delimiter)
{
	return (ft_strcmp(line, delimiter) == 0);
}

static void	write_line_fd(const char *line, bool quoted,
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

void	heredoc_from_string(t_heredoc *hdoc, t_cli *cli, int write_fd)
{
	const char	*p;
	char		*line;
	const char	*nl;

	p = cli->s_heredoc;
	while (*p)
	{
		nl = ft_strchr(p, '\n');
		line = extract_heredoc_line(p, nl);
		if (!line)
		{
			close(write_fd);
			exit(1);
		}
		if (is_delimiter(line, hdoc->delimiter))
		{
			free(line);
			break ;
		}
		write_line_fd(line, hdoc->quoted, *cli->env, write_fd);
		free(line);
		if (!nl)
			break ;
		p = nl + 1;
	}
}
