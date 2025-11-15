/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 02:35:57 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_redirection(char *curr, char *next)
{
	if (!ft_strchr("<>", curr[0]))
		return (0);
	if (!next || next[0] == '\0')
	{
		ft_perror(curr, SYN_ERR);
		return (1);
	}
	if (ft_strchr("|&", next[0]))
	{
		ft_perror(curr, SYN_ERR);
		return (1);
	}
	return (0);
}

static void	prepare_neighbors(t_token *tokens, int len, int index,
		char **curr_next)
{
	curr_next[0] = tokens[index].value;
	if (index + 1 < len)
		curr_next[1] = tokens[index + 1].value;
	else
		curr_next[1] = NULL;
}

static int	process_segment(t_token *tokens, int len, int *index, char **curr)
{
	char	*neighbors[2];
	char	*value;
	int		command;

	command = 0;
	while (*index < len)
	{
		prepare_neighbors(tokens, len, *index, neighbors);
		value = neighbors[0];
		if (value && value[0] == '|' && value[1] == '\0')
			break ;
		*curr = value;
		if (!value || value[0] == '\0')
		{
			(*index)++;
			continue ;
		}
		if (handle_redirection(value, neighbors[1]))
			return (-1);
		if (!ft_strchr("|&<>", value[0]))
			command = 1;
		(*index)++;
	}
	return (command);
}

static char	*error_token(t_token *tokens, int len, int index, char *curr)
{
	if (index < len && tokens[index].value)
		return (tokens[index].value);
	return (curr);
}

static void	skip_double_operator(t_token *tokens, int len, int *index)
{
	char	*neighbors[2];

	if (*index + 1 >= len)
		return ;
	prepare_neighbors(tokens, len, *index, neighbors);
	if (!neighbors[0] || !neighbors[1])
		return ;
	if (neighbors[0][0] == '|' && neighbors[1][0] == '|')
	{
		(*index)++;
		return ;
	}
	if (neighbors[0][0] == '&' && neighbors[1][0] == '&')
		(*index)++;
}

int	ft_check_errors(t_token *tokens, int len)
{
	int		status;
	int		index;
	char	*curr;

	index = 0;
	curr = NULL;
	while (index < len)
	{
		status = process_segment(tokens, len, &index, &curr);
		if (status == -1)
			return (1);
		if (status == 0)
		{
			ft_perror(error_token(tokens, len, index, curr), SYN_ERR);
			return (1);
		}
		skip_double_operator(tokens, len, &index);
		index++;
	}
	return (0);
}
