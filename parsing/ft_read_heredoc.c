/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:46:06 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 13:19:09 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	init_heredoc_storage(t_cli *cli)
{
	if (cli->s_heredoc)
		return (0);
	cli->s_heredoc = ft_strdup("");
	if (!cli->s_heredoc)
		return (2);
	return (0);
}

static int	append_line_with_nl(t_cli *cli, char *line)
{
	char	*with_nl;
	char	*tmp;

	with_nl = ft_strjoin(line, "\n");
	if (!with_nl)
		return (2);
	tmp = ft_strjoin(cli->s_heredoc, with_nl);
	free(with_nl);
	if (!tmp)
		return (2);
	free(cli->s_heredoc);
	cli->s_heredoc = tmp;
	return (0);
}

static int	heredoc_loop(t_cli *cli, char *delim)
{
	char	*line;
	int		ret;
	size_t	len;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (ft_here_error(delim), free(delim), 0);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ret = append_line_with_nl(cli, line);
		free(line);
		if (ret)
			return (free(delim), cli->status = 2, 2);
	}
	return (-1);
}

static int	expand_if_needed(t_cli *cli, int *option, char *delim)
{
	if (cli->s_heredoc)
	{
		cli->s_heredoc = ft_expand_heredoc(*option, cli);
		if (!cli->s_heredoc)
		{
			free(delim);
			cli->status = 2;
			return (2);
		}
	}
	return (0);
}

int	ft_read_heredoc(t_cli *cli, int *option, char *delim)
{
	int	ret;

	ret = init_heredoc_storage(cli);
	if (ret)
	{
		free(delim);
		return (2);
	}
	ret = heredoc_loop(cli, delim);
	if (ret != -1)
		return (ret);
	ret = expand_if_needed(cli, option, delim);
	if (ret)
		return (ret);
	free(delim);
	return (0);
}
