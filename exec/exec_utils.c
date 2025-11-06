/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:59:39 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 12:22:30 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_directory(const char *path)
{
    struct stat st;

    if (stat(path, &st) == 0)
        return S_ISDIR(st.st_mode);
    return false;
}

bool has_pipes_or_redirs(t_cli *cli)
{
    while (cli)
    {
        if (cli-> infile || cli->outfile || cli->heredoc)
            return (true);
        if (cli->next)
            return (true);
        cli = cli->next;
    }
    return (false);
}
void check_command_errors(t_cli *cmd) 
{
    if (!cmd || !cmd->args || !cmd->args[0] || !cmd->cmd)
    {
        write(STDERR_FILENO, "minishell: Empty or invalid command\n", 36);
        exit(127);
    }
    if (cmd->args[0] && ft_strcmp(cmd->args[0], ".") == 0) 
    {
        fprintf(stderr, "minishell: .: Not supported\n");
        exit(127);
    }
    if (!cmd->cmd || ft_strcmp(cmd->cmd, "") == 0 ||
    !cmd->args || !cmd->args[0] || ft_strcmp(cmd->args[0], "") == 0)
    {
    write(STDERR_FILENO, "minishell: Empty command\n", 25);
    exit(127);
    }

    if (is_directory(cmd->cmd)) 
    {
        write(STDERR_FILENO, "minishell: .: is a directory\n", 29);
        exit(126);
    }

}
