/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:16:18 by dogs              #+#    #+#             */
/*   Updated: 2025/10/18 15:52:40 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_trunc(char *filename, t_cli *cli)
{
	if (cli->outfile)
		free(cli->outfile);
	cli->outfile = ft_strdup(filename);
	cli->r_mode = WRITE;
    cli->breaks_pipe = true;
}

int	ft_append(char *token, t_cli *cli)
{
	int	i;

	if (!token)
		return (ft_perror(">>", SYN_ERR), 0);
	if (!cli)
		return (0);
	i = 0;
	free(cli->outfile);
	cli->r_mode = APPEND;
	cli->breaks_pipe = true;
	if (ft_strchr(QUOTES, token[i]) && (i == 0 || (i > 0 && token[i - 1] != '\\')))
		cli->outfile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->outfile = ft_strdup(token + i);
	if (!cli->outfile)
		return (perror("malloc : "), 0);
	return (1);
}
int	ft_outfile(char *token, t_cli *cli)
{
	int	i;

	if (!token)
		return (ft_perror(">", SYN_ERR), 0);
	if (!cli)
		return (0);
	i = 0;
	free(cli->outfile);
	cli->r_mode = 0;
	if (ft_strchr(QUOTES, token[i]) && (i == 0 || (i > 0 && token[i - 1] != '\\')))
		cli->outfile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->outfile = ft_strdup(token + i);
	if (!cli->outfile)
		return (0);
	return (1);
}

int	ft_infile(char *token, t_cli *cli)
{
	int	i;

	if (!cli)
		return (0);
	i = 0;
	if (!token)
		return (ft_perror("<", SYN_ERR), 0);
	free(cli->infile);
	free(cli->heredoc);
	cli->heredoc = NULL;
	if (ft_strchr(QUOTES, token[i]) && (i == 0 || (i > 0 && token[i - 1] != '\\')))
		cli->infile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->infile = ft_strdup(token + i);
	if (!cli->infile)
		return (0);
	return (1);
}