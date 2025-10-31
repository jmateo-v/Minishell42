/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:46:30 by dogs              #+#    #+#             */
/*   Updated: 2025/10/21 16:26:06 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_pipe(const char *s)
{
    return (strcmp(s, "|") == 0);
}

int ft_token_count(t_token *tokens)
{
    int count = 0;

    if (!tokens)
        return 0;

    while (tokens[count].segments)
        count++;

    return count;
}


int     ft_args(char *token, t_cli *cli, int pos)
{
	char	**t;

	if (!token || !cli)
		return (0);
	if (!cli->args)
	{
		cli->args = (char **)ft_calloc(2, sizeof(char *));
		if (!cli->args)
			return (perror("malloc"), 0);
		cli->args[1] = NULL;
		cli->args[0] = ft_strdup(token);
		if (!cli->args[0])
			return (perror("malloc"), 0);
	}
	else
	{
		t = (char **)ft_add_str((void *)cli->args, (char *)token, pos);
		if (!t)
			return (perror("malloc"), 0);
		ft_free_str_array(&cli->args);
		cli->args = t;
	}
	cli->n_tokens++;
	return (1);
}



char	*ft_cmd_path(char *env_path, char *cmd)
{
	int		i;
	char	**path;
	char	*cmd_path;
	char	*t;

	i = 0;
	path = ft_split(env_path, ':');
	if (!path)
		return (perror("malloc"), NULL);
	while (path[i])
	{
		t = ft_strjoin(path[i], "/");
		if (!t)
			return (ft_free_str_array(&path), perror("malloc"), NULL);
		cmd_path = ft_strjoin(t, cmd);
		free(t);
		if (!cmd_path)
		    return (ft_free_str_array(&path), perror("malloc"), NULL);
		if (!access(cmd_path, X_OK))
			return (ft_free_str_array(&path), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_str_array(&path), NULL);
}


int	ft_cmd(char	*token, t_cli *cli)
{
	if (!token)
		return (0);
	if (!ft_strcmp(token, "echo")
	|| !ft_strcmp(token, "cd") || !ft_strcmp(token, "pwd")
	|| !ft_strcmp(token, "export") || !ft_strcmp(token, "unset")
	|| !ft_strcmp(token, "env") || !ft_strcmp(token, "exit"))
		return (cli->is_builtin = 1, cli->cmd = ft_strdup(token), 1);
	if (token && ft_strchr(token, '/'))
		cli->cmd = ft_strdup(token);
	else
		cli->cmd = ft_cmd_path(getenv("PATH"), token);
	if (!cli->cmd)
		cli->cmd = ft_strdup(token);
	return (1);
}