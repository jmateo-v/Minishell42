/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:59:11 by dogs              #+#    #+#             */
/*   Updated: 2025/10/30 17:28:51 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_list(t_cli *cli)
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
		if (cli->heredoc)
			printf("heredoc %d = %s\n", node, cli->heredoc);
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
}

void    ft_perror(char *token, char *msg)
{
    char    *t;
    char    *err;

    if (!msg)
        msg = "(null)";
    if (!token)
        token = "(null)";

    t = ft_strjoin(msg, token);
    if (!t)
        return;

    err = ft_strjoin(t, "'\n");
    free(t);
    if (!err)
        return;

    write(2, err, ft_strlen(err));
    free(err);
}

static void free_segments(t_segment *segs)
{
    if (!segs) return;
    for (int j = 0; segs[j].value != NULL; j++)
        free(segs[j].value);
    free(segs);
}

void ft_free_tokens(t_token *tokens)
{
    if (!tokens) return;
    int i = 0;
    while (1) {
        if (tokens[i].segments == NULL && tokens[i].value == NULL)
            break;

        if (tokens[i].value)
            free(tokens[i].value);

        free_segments(tokens[i].segments);

        i++;
    }
    free(tokens);
}

t_cli	*ft_init_node(int len, t_shenv **env, int op)
{
	t_cli *cli;

	if (len <= 0)
		return (NULL);
	cli = (t_cli *)ft_calloc(1, sizeof(t_cli));
	if (!cli)
		return (perror("malloc : "), NULL);
	cli->cmd = NULL;
	cli->args = NULL;
	cli->env = env;
	if (env && !cli->env)
		perror("malloc : ");
	cli->infile = NULL;
	cli->outfile = NULL;
	cli->heredoc = NULL;
	cli->heredoc_fd = -1;
	cli->is_builtin = 0;
	cli->next = NULL;
	cli->r_mode = WRITE;
	cli->n_tokens = len;
	cli->group = 1;
	cli->op = op;
	cli->status = 0;
	cli->last_status = 0;
	cli->breaks_pipe = false;
	return (cli);
}

void	ft_free_list(t_cli **cli)
{
	t_cli		*node;
	t_cli		*next_node;

	if (!cli || !*cli)
		return ;
	node = *cli;
	while (node)
	{
		next_node = node->next;
		free(node->cmd);
		node->cmd = NULL;
		free(node->heredoc);
		node->heredoc = NULL;
		free(node->infile);
		node->infile = NULL;
		free(node->outfile);
		node->outfile = NULL;
		ft_free_str_array(&node->args);
		node->args = NULL;
		free(node);
		node = next_node;
	}
	*cli = NULL;
	return ;
}

void	ft_free_node(t_cli *cli)
{
	if (!cli)
		return ;
	free(cli->cmd);
	cli->cmd = NULL;
	free(cli->heredoc);
	cli->heredoc = NULL;
	free(cli->infile);
	cli->infile = NULL;
	free(cli->outfile);
	cli->outfile = NULL;
	ft_free_str_array(&cli->args);
	cli->args = NULL;
	free(cli);
	cli = NULL;
	return ;
}

int ft_trim_s_len(char *line)
{
	size_t		i;
	int		len;

	i = 0;
	len = 0;
	while (line && i < ft_strlen(line))
	{
		if (ft_strchr(QUOTES, line[i]) && (i == 0 || (i > 0 && line[i - 1] != '\\')))
		{
			if (ft_quoted_len(line + i, line[i])  <= 0)
				return (-1);
			len += ft_quoted_len(line + i, line[i]);
			i += ft_quoted_len(line + i, line[i]);
			continue ;
		}
		while (ft_isspace(line[i]) && (( i + 1) >= ft_strlen(line) || ft_isspace(line[i + 1])))
			i++;
		i++;
		len++;
	}
	return (len);
}
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

char	*ft_trim_delim(char *token, int *option)
{
	char	*delim;
	int		i;

	if (!token)
		return (NULL);
	i = 0;
	if (ft_strchr(QUOTES, token[i]) && (i == 0 || (i > 0 && token[i - 1] != '\\')))
	{
		if (token[i] == '\"')
			*option = 1;
		delim = ft_escape_quotes(token + i);
	}
	else
		delim = ft_strdup(token + i);
	return (delim);
}