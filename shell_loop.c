/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:56 by dogs              #+#    #+#             */
/*   Updated: 2025/11/19 19:10:48 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void print_tokens(t_token *tokens)
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
}*/
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
	//print_tokens(tokens);
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
