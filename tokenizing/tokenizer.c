/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:58:10 by dogs              #+#    #+#             */
/*   Updated: 2025/11/03 18:46:23 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_tokenize_cl(char *line, t_cli *cli)
{
	t_token	*tokens;

	if (!line)
		return (NULL);
	cli->n_tokens = ft_precount_tokens(line);
	line = ft_trim_spaces(line);
	if (!line)
		return(write(2, ERR_OPEN_Q, ft_strlen(ERR_OPEN_Q)), NULL);
	tokens = ft_token_sep(line);
	if (!tokens)
		return (NULL);
	tokens = ft_expand_tokens(tokens, &(cli->n_tokens), cli);
	
	if (!tokens)
		return (NULL);
	if (new_ft_check_errors(tokens, ft_token_count(tokens)))
		return (ft_free_tokens(tokens), NULL);
	ft_finalize_tokens(tokens);
	return (tokens);
}