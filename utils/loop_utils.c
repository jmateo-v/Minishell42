/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:02:18 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 18:06:41 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_read_with_hook(char *cl)
{
	if (cl)
		free(cl);
	rl_event_hook = ft_sig_hook;
	cl = ft_read_input();
	rl_event_hook = NULL;
	return (cl);
}

int	ft_check_signal(t_cli *cli)
{
	if (g_sig_rec)
	{
		ft_reset_signal(cli);
		return (1);
	}
	return (0);
}

int	ft_check_eof(char *cl)
{
	if (!cl)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			write(1, "exit\n", 5);
		return (1);
	}
	return (0);
}

void	ft_handle_command(char *cl, t_cli *cli)
{
	if (cl[0] == '\0')
		return ;
	add_history(cl);
	cli->status = ft_process_command(cl, cli);
	cli->last_status = cli->status;
}
