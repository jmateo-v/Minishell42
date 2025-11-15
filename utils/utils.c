/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:59:11 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 23:08:35 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror(char *token, char *msg)
{
	char	*t;
	char	*err;

	if (!msg)
		msg = "(null)";
	if (!token)
		token = "(null)";
	t = ft_strjoin(msg, token);
	if (!t)
		return ;
	err = ft_strjoin(t, "'\n");
	free(t);
	if (!err)
		return ;
	write(2, err, ft_strlen(err));
	free(err);
}

static void	ft_init_node_fields(t_cli *cli, int len, t_shenv **env, int op)
{
	cli->cmd = NULL;
	cli->args = NULL;
	cli->env = env;
	if (env && !cli->env)
		perror("malloc : ");
	cli->infile = NULL;
	cli->outfile = NULL;
	cli->heredocs = NULL;
	cli->num_heredocs = 0;
	cli->s_heredoc = NULL;
	cli->is_builtin = 0;
	cli->next = NULL;
	cli->r_mode = WRITE;
	cli->n_tokens = len;
	cli->group = 1;
	cli->op = op;
	cli->status = 0;
	cli->last_status = 0;
	cli->breaks_pipe = false;
}

t_cli	*ft_init_node(int len, t_shenv **env, int op)
{
	t_cli	*cli;

	if (len <= 0)
		return (NULL);
	cli = (t_cli *)ft_calloc(1, sizeof(t_cli));
	if (!cli)
		return (perror("malloc : "), NULL);
	ft_init_node_fields(cli, len, env, op);
	return (cli);
}

int	ft_trim_s_len(char *line)
{
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	while (line && i < ft_strlen(line))
	{
		if (ft_strchr(QUOTES, line[i]) && (i == 0
				|| (i > 0 && line[i - 1] != '\\')))
		{
			if (ft_quoted_len(line + i, line[i]) <= 0)
				return (-1);
			len += ft_quoted_len(line + i, line[i]);
			i += ft_quoted_len(line + i, line[i]);
			continue ;
		}
		while (ft_isspace(line[i]) && ((i + 1) >= ft_strlen(line)
				|| ft_isspace(line[i + 1])))
			i++;
		i++;
		len++;
	}
	return (len);
}

char	*ft_trim_delim(char *token, int *option)
{
	char	*delim;
	int		i;

	if (!token)
		return (NULL);
	i = 0;
	if (ft_strchr(QUOTES, token[i])
		&& (i == 0 || (i > 0 && token[i - 1] != '\\')))
	{
		if (token[i] == '\"')
			*option = 1;
		delim = ft_escape_quotes(token + i);
	}
	else
		delim = ft_strdup(token + i);
	return (delim);
}
