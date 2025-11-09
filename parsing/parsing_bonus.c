/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/06 19:53:05 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parse(t_token *tokens, t_cli *cli)
{
	int		i;
	int		len;
	int		group;
	t_cli	*next_cli;
	int		step;

	if (!tokens || !cli)
		return (2);
	i = 0;
	step = 1;
	group = 1;
	len = ft_token_count(tokens);
	cli->n_tokens = 1;
	while (i < len)
	{
		if (!tokens[i].value)
		{
			i++;
			continue ;
		}
		if (tokens[i].value)
		{
			if (strcmp(tokens[i].value, "&") == 0 && (i + 1) < len
				&& tokens[i + 1].value && strcmp(tokens[i + 1].value, "&") == 0)
				step = 2;
			else if (strcmp(tokens[i].value, "&&") == 0)
				step = 1;
			if ((step == 2 && strcmp(tokens[i].value, "&") == 0
					&& strcmp(tokens[i + 1].value, "&") == 0)
				|| (step == 1 && strcmp(tokens[i].value, "&&") == 0))
			{
				cli->op = AND;
				next_cli = ft_init_node(cli->n_tokens, cli->env, 0);
				if (!next_cli)
					return (perror("malloc : "), 2);
				next_cli->n_tokens = 1;
				cli->next = next_cli;
				cli = cli->next;
				i += step;
				continue ;
			}
		}
		if (tokens[i].value)
		{
			if (strcmp(tokens[i].value, "|") == 0
				&& (i + 1) < len && tokens[i + 1].value
				&& strcmp(tokens[i + 1].value, "|") == 0)
				step = 2;
			else if (strcmp(tokens[i].value, "||") == 0)
				step = 1;
			if ((step == 2 && strcmp(tokens[i].value, "|") == 0
					&& strcmp(tokens[i + 1].value, "|") == 0) || (step == 1
					&& strcmp(tokens[i].value, "||") == 0))
			{
				cli->op = OR;
				next_cli = ft_init_node(cli->n_tokens, cli->env, 0);
				if (!next_cli)
					return (perror("malloc : "), 2);
				next_cli->n_tokens = 1;
				cli->next = next_cli;
				cli = cli->next;
				i += step;
				continue ;
			}
		}
		if (tokens[i].value && !ft_strncmp(tokens[i].value, ">>", 2))
		{
			if (i + 1 >= len)
				return (perror("missing target for >>, SYN ERR"),
					ft_free_tokens(tokens), 2);
			ft_append(tokens[i + 1].value, cli);
			i += 2;
			continue ;
		}
		else if (tokens[i].value[0] != '\0'
			&& ft_strcmp(tokens[i].value, "<<") == 0)
		{
			if (i + 1 >= len)
				return (ft_perror("missing target for <<", SYN_ERR),
					ft_free_tokens(tokens), 2);
			if (ft_heredoc(tokens[i + 1].value, cli) == 130)
				return (130);
			i += 2;
			continue ;
		}
		else if (tokens[i].value
			&& !ft_strncmp(tokens[i].value, ">", 1)
			&& ft_strlen(tokens[i].value) == 1)
		{
			if (i + 1 >= len)
				return (ft_perror("missing target for >", SYN_ERR), 2);
			ft_trunc(tokens[i + 1].value, cli);
			i += 2;
			continue ;
		}
		else if (tokens[i].value && !ft_strncmp(tokens[i].value, "<", 1)
			&& ft_strlen(tokens[i].value) == 1)
		{
			if (i + 1 >= len)
				return (ft_perror("missing target for <", SYN_ERR), 2);
			ft_infile(tokens[i + 1].value, cli);
			i += 2;
			continue ;
		}
		else if (tokens[i].value && is_pipe(tokens[i].value))
		{
			cli->next = ft_parse_pipe(tokens[i].value, cli);
			if (!cli->next)
				return (2);
			cli = cli->next;
		}
		else
			ft_parse_token(tokens, i, cli, &group);
		i++;
	}
	return (0);
}
