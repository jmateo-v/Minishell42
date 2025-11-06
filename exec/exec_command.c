/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:08:00 by dogs              #+#    #+#             */
/*   Updated: 2025/11/06 11:50:20 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **prepare_env(t_cli *cmd)
{
    char **env;
    
    env = ft_getshenv(*(cmd->env));
    if (!env && cmd->env)
        exit(2);
    return env;
}
void run_execve(t_cli *cmd, char **env) 
{
    execve(cmd->cmd, cmd->args, env);
    int err = errno;
    ft_free_env(cmd->env);
    ft_free_str_array(&env);
    ft_free_list(&cmd);
    perror("execve");

    if (err == ENOENT || err == ENOEXEC)
        exit(127);
    else
        exit(126);
}

void handle_child(t_cli *cmd) 
{
    ft_set_sig(CHILD);
    char **env = prepare_env(cmd);
    check_command_errors(cmd);
    run_execve(cmd, env);
}

int handle_parent(pid_t pid, t_cli *cmd) 
{
    waitpid(pid, &cmd->status, 0);
    ft_set_sig(PARENT);
    if (WIFSIGNALED(cmd->status)) 
    {
        if (WTERMSIG(cmd->status) == SIGINT)
            write(STDOUT_FILENO, "\n", 1);
        if (WTERMSIG(cmd->status) == SIGQUIT)
            write(STDOUT_FILENO, "Quit (Core dumped)\n", 19);
        return (128 + WTERMSIG(cmd->status));
    }
    else if (WIFEXITED(cmd->status)) 
        return (WEXITSTATUS(cmd->status));
    else 
        return (cmd->status);
}



int execute_command(t_cli *cmd)
{
    pid_t   pid;
    
    if (!cmd || !cmd->cmd)
        return (-1);
    ft_set_sig(IGNORE);
    pid = fork();
    if (pid == 0)
        handle_child(cmd);
    else if (pid > 0)
        return (handle_parent(pid, cmd));
    else
    {
        perror("fork failed");
        ft_set_sig(PARENT);
        return (-1);
    }
    return(-1);
}