/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dansanc3          #+#    #+#             */
/*   Updated: 2025/11/15 12:35:02 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell_bonus.h"

int	handle_redirection(char *curr, char *next)
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
