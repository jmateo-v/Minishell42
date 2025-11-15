/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:26:11 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 23:52:11 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_cli_heredocs(t_cli *cli)
{
	int	i;

	if (!cli->heredocs)
		return ;
	i = 0;
	while (i < cli->num_heredocs)
	{
		if (cli->heredocs[i].delimiter)
			free(cli->heredocs[i].delimiter);
		if (cli->heredocs[i].fd != -1)
			close(cli->heredocs[i].fd);
		i++;
	}
	free(cli->heredocs);
	cli->heredocs = NULL;
	cli->num_heredocs = 0;
}

static void	ft_free_cli_fields(t_cli *cli)
{
	if (!cli)
		return ;
	if (cli->cmd)
		free(cli->cmd);
	cli->cmd = NULL;
	if (cli->infile)
		free(cli->infile);
	cli->infile = NULL;
	if (cli->outfile)
		free(cli->outfile);
	cli->outfile = NULL;
	if (cli->args)
		ft_free_str_array(&cli->args);
	cli->args = NULL;
	if (cli->s_heredoc)
		free(cli->s_heredoc);
	cli->s_heredoc = NULL;
	ft_free_cli_heredocs(cli);
}

void	ft_reset_list(t_cli *cli)
{
	t_cli	*next;

	if (!cli)
		return ;
	next = cli->next;
	if (next)
	{
		ft_free_list(&next);
		cli->next = NULL;
	}
	ft_free_cli_fields(cli);
	cli->is_builtin = 0;
	cli->r_mode = 0;
	cli->group = 0;
	cli->op = 0;
}

t_cli	*ft_setup_shell(char **envp, t_shenv **env)
{
	rl_catch_signals = 0;
	ft_set_sig(PARENT);
	enable_echoctl();
	*env = ft_load_env(envp);
	return (ft_init_node(1, env, 0));
}

void	ft_cleanup_shell(t_cli **cli, t_shenv **env)
{
	ft_free_list(cli);
	ft_free_env(env);
}
