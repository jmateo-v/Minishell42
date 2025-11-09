/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/09 22:40:45 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_next_curr(char *next, char *curr, int flag_next, int flag_curr)
{
	if (flag_next)
		free(next);
	if (flag_curr)
		free(curr);
}

int	ft_check_errors(t_token *tokens, int len)
{
	int		i;
	int		has_command;
	char	*curr;
	char	*next;
	int		flag_curr;
	int		flag_next;

	i = 0;
	flag_curr = 0;
	flag_next = 0;
	has_command = 0;
	while (i < len)
	{
		has_command = 0;
		while (i < len && !(tokens[i].value[0] == '|'
				&& tokens[i].value[1] == '\0'))
		{
			if (tokens[i].value)
			{
				curr = malloc(ft_strlen(tokens[i].value) + 1);
				if (curr)
					ft_strcpy(curr, tokens[i].value);
				flag_curr = 1;
			}
			if (i + 1 < len && tokens[i + 1].value)
			{
				next = malloc(ft_strlen(tokens[i + 1].value) + 1);
				if (next)
					ft_strcpy(next, tokens[i + 1].value);
				flag_next = 1;
			}
			if (!curr || curr[0] == '\0')
			{
				i++;
				continue ;
			}
			if (ft_strchr("<>", curr[0]))
			{
				if (!next || ft_strchr("|&", next[0]))
				{
					free_next_curr(next, curr, flag_next, flag_curr);
					return (ft_perror(curr, SYN_ERR), 1);
				}
			}
			if (!ft_strchr("|&<>", curr[0]))
				has_command = 1;
			i++;
		}
		if (!has_command)
		{
			free_next_curr(next, curr, flag_next, flag_curr);
			return (ft_perror(tokens[i].value, SYN_ERR), 1);
		}
		if (i + 1 < len && tokens[i].value && tokens[i + 1].value)
		{
			if ((tokens[i].value[0] == '|' && tokens[i + 1].value[0] == '|')
				|| (tokens[i].value[0] == '&' && tokens[i + 1].value[0] == '&'))
				i++;
		}
		i++;
	}
	free_next_curr(next, curr, flag_next, flag_curr);
	return (0);
}
