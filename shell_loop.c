/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:56 by dogs              #+#    #+#             */
/*   Updated: 2025/11/21 16:09:04 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_input(void)
{
	char	*cl;
	size_t	len;

	cl = NULL;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
	{
		rl_outstream = stderr;
		cl = readline("\033[1;38;5;117mminishell\033[0m$ ");
		if (!cl)
		{
			free(cl);
			return (NULL);
		}
	}
	else
	{
		cl = get_next_line(STDIN_FILENO);
		if (cl)
		{
			len = ft_strlen(cl);
			if (len > 0 && cl[len - 1] == '\n')
				cl[len - 1] = '\0';
		}
	}
	return (cl);
}

int	ft_process_command(char *cl, t_cli *cli)
{
	t_token	*tokens;

	if (!cl || cl[0] == '\0')
		return (1);
	tokens = ft_tokenize_cl(cl, cli);
	if (!tokens)
		return (2);
	cli->status = ft_parse(tokens, cli);
	cli->status = ft_execute(cli);
	ft_free_tokens(tokens);
	ft_reset_list(cli);
	return (cli->status);
}

int	shell_loop(t_cli *cli)
{
	char	*cl;

	cl = NULL;
	while (1)
	{
		cl = ft_read_with_hook(cl);
		if (ft_check_signal(cli))
			continue ;
		if (ft_check_eof(cl))
			break ;
		ft_handle_command(cl, cli);
	}
	rl_clear_history();
	return (cli->status);
}
