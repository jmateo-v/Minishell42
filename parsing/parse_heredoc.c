/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:21:41 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 13:05:35 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc_len(char *line)
{
	int	i;
	int	len;

	i = 0;
	while (i < (int)ft_strlen(line) && i < 2 && ft_strchr(REDIR_S, line[i]))
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (i < (int)ft_strlen(line) && line[i])
	{
		if (i < (int)ft_strlen(line) && ft_strchr(QUOTES, line[i])
			&& (i == 0 || (i > 0 && line[i - 1] != '\\')))
		{
			len = ft_quoted_len(line + i, line[i]);
			if (len <= 0)
				return (-1);
			i += (len + 1);
			continue ;
		}
		if (ft_strchr(SEP_STR, line [i]))
			return (i);
		i++;
	}
	return (i);
}

char	*ft_expand_heredoc(int option, t_cli *cli)
{
	char	*t;

	t = NULL;
	if (option && cli->s_heredoc)
	{
		t = ft_expand_line(cli->s_heredoc, cli);
		if (!t)
			return (NULL);
		cli->s_heredoc = t;
	}
	return (cli->s_heredoc);
}

void	ft_here_error(char *delim)
{
	char	*t;
	char	*error_msg;

	t = ft_strjoin(HERE_ERR, delim);
	error_msg = ft_strjoin(t, "')\n");
	if (!error_msg)
	{
		perror("malloc : ");
		return ;
	}
	write(2, error_msg, ft_strlen(error_msg));
	free(error_msg);
	free(t);
	return ;
}

static void	ft_free_prev(t_cli *cli)
{
	free(cli->s_heredoc);
	free(cli->infile);
	cli->infile = NULL;
	cli->s_heredoc = NULL;
}

int	ft_script_heredoc(char *token, t_cli *cli)
{
	char	*delim;
	int		option;
	int		status;

	if (!cli)
		return (printf("!cli\n"), 2);
	ft_free_prev(cli);
	if (!token)
		return (ft_perror("<<", SYN_ERR), 2);
	delim = ft_trim_delim(token, &option);
	if (!delim)
		return (cli->status = 2, 2);
	option = 0;
	status = ft_read_heredoc(cli, &option, delim);
	return (status);
}
