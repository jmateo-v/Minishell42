/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:56 by dogs              #+#    #+#             */
/*   Updated: 2025/11/15 17:03:22 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	ft_print_list(t_cli *cli)
{
	size_t	i = 0;
	int	node = 0;

	if (!cli)
		return ;
	while (cli)
	{
		if (!cli)
			return ;
		if (cli->cmd)
			printf("cmd %d = %s\n", node, cli->cmd);
		if (cli->infile)
			printf("infile %d = %s\n", node, cli->infile);
		if (cli->outfile)
			printf("outfile %d = %s\n", node, cli->outfile);
		if (cli->is_builtin)
			printf("is_builtin %d = %d\n", node, cli->is_builtin);
		if (cli->r_mode)
			printf("r_mode %d = %d\n", node, cli->r_mode);
		printf("op = %d\n", cli->op);
		printf("group = %d\n", cli->group);
		while (cli->args && i < ft_ptr_array_len((void **)cli->args))
		{
			printf("args[%ld] %d = %s\n", i, node, cli->args[i]);
			i++;
		}
		i = 0;
		cli = cli->next;
		node++;
	}
}*/

void print_tokens(t_token *tokens)
{
    if (!tokens) {
        printf("No tokens to print.\n");
        return;
    }

    for (int k = 0; tokens[k].segments != NULL; k++)  // Check for null segments array explicitly
    {
        printf("token[%d]:\n", k);

        if (tokens[k].segments == NULL) {
            printf("  Warning: Token %d has no segments!\n", k);
        }

        for (int s = 0; tokens[k].segments[s].value != NULL; s++)  // Check for null segment values explicitly
        {
            if (tokens[k].segments[s].value == NULL) {
                printf("  Warning: Segment %d in token[%d] is NULL!\n", s, k);
            } else {
                printf("  segment[%d]: [%s] (type=%d)\n",
                       s, tokens[k].segments[s].value, tokens[k].segments[s].type);
            }
        }

        if (tokens[k].value != NULL)
        {
            printf("  finalized value: [%s]\n", tokens[k].value);
        }
        else
        {
            printf("  Warning: Token[%d] has no finalized value!\n", k);
        }
    }
}

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
	print_tokens(tokens);
	cli->status = ft_parse(tokens, cli);
	//ft_print_list(cli);
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
