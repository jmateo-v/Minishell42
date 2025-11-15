/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:02:43 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 23:12:12 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_heredocs(t_cli *node)
{
	int	i;

	if (!node->heredocs)
		return ;
	i = 0;
	while (i < node->num_heredocs)
	{
		if (node->heredocs[i].delimiter)
			free(node->heredocs[i].delimiter);
		if (node->heredocs[i].fd != -1)
			close(node->heredocs[i].fd);
		i++;
	}
	free(node->heredocs);
	node->heredocs = NULL;
	node->num_heredocs = 0;
}

static void	ft_free_node(t_cli *node)
{
	free(node->cmd);
	node->cmd = NULL;
	free(node->infile);
	node->infile = NULL;
	free(node->outfile);
	node->outfile = NULL;
	free(node->s_heredoc);
	ft_free_str_array(&node->args);
	node->args = NULL;
	ft_free_heredocs(node);
	free(node);
}

void	ft_free_list(t_cli **cli)
{
	t_cli	*node;
	t_cli	*next_node;

	if (!cli || !*cli)
		return ;
	node = *cli;
	while (node)
	{
		next_node = node->next;
		ft_free_node(node);
		node = next_node;
	}
	*cli = NULL;
}
