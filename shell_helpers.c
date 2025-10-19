/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:26:11 by dogs              #+#    #+#             */
/*   Updated: 2025/10/18 15:26:17 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_rec = 0;

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
	free(cli->cmd);
	cli->cmd = NULL;
	free(cli->heredoc);
	cli->heredoc = NULL;
	free(cli->infile);
	cli->infile = NULL;
	free(cli->outfile);
	cli->outfile = NULL;
	if (cli -> args)
	{
		ft_free_str_array(&cli->args);
		cli->args = NULL;
	}
	cli->is_builtin = 0;
	cli->r_mode = 0;
	cli->group = 0;
	cli->op = 0;
}
t_cli *ft_setup_shell(char **envp, t_shenv **env)
{
    rl_catch_signals = 0;
    ft_set_sig(PARENT);
    *env = ft_load_env(envp);
    return ft_init_node(1, env, 0);
}
void ft_cleanup_shell(t_cli **cli, t_shenv **env)
{
    ft_free_list(cli);
    ft_free_env(env);
}