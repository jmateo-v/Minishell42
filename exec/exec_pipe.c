/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:21:28 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 15:34:20 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exit_perror(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
void    setup_child(t_cli *cmd, int prev_pipe, int *pipe_fd)
{
    int fd;
    int flags;

    if (cmd->heredoc_fd != -1)
    {
        dup2(cmd->heredoc_fd, STDIN_FILENO);
        close(cmd->heredoc_fd);
    }
    else if (cmd->infile)
    {
        fd = open(cmd->infile, O_RDONLY);
        if (fd < 0)
            exit_perror(cmd->infile);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    else if (prev_pipe != -1)
    {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }
    if (cmd->outfile)
    {
        flags = O_WRONLY | O_CREAT;
        if(cmd->r_mode == WRITE)
            flags |= O_TRUNC;
        else if (cmd->r_mode == APPEND)
            flags |= O_APPEND;
        fd = open(cmd->outfile, flags, 0644);
        if (fd < 0)
            exit_perror(cmd->outfile);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    else if (pipe_fd)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }
    if (prev_pipe != -1)
        close(prev_pipe);
    if (pipe_fd && pipe_fd[0] != -1)
        close(pipe_fd[0]);
}

void exec_command(t_cli *cmd)
{
    char **env;
    int status;

    env = ft_getshenv(*(cmd->env));
    if (cmd->env && !env)
        exit(2);

    if (cmd->is_builtin)
    {
        status = execute_builtin(cmd);
        ft_free_str_array(&env);
        exit(status);
    }
    if (cmd->args[0] && strcmp(cmd->args[0], ".") == 0)
    {
        fprintf(stderr, "minishell: .: Not supported\n");
        exit(127);
    }
    if (is_directory(cmd->cmd))
    {
        write(STDERR_FILENO, "minishell: .: is a directory\n", 29);
        exit(126);
    }
    execve(cmd->cmd, cmd->args, env);
    perror("execve");
    ft_free_str_array(&env);
    if (errno == ENOENT || errno == ENOEXEC)
        exit(127);
    else
        exit(126);
}


int wait_for_children(pid_t last_pid, pid_t *child_pids, int child_count)
{
    int remaining;
    int status;
    int last_status;
    bool sigint_sent;
    pid_t wpid;

    remaining = child_count;
    last_status = 0;
    sigint_sent = false;

    while (remaining > 0)
    {
        wpid = waitpid(-1, &status, 0);
        if (wpid == -1)
        {
            if (errno == EINTR)
                continue;
            else
                break;
        }
        remaining --;
        if (wpid == last_pid)
            last_status = status;
        if (g_sig_rec && !sigint_sent)
        {
            int i = 0;
            while (i < child_count)
            {
                kill(child_pids[i], SIGINT);
                i++;
            }
            sigint_sent = true;
        }
    }
    if (WIFEXITED(last_status))
        return WEXITSTATUS(last_status);
    else if (WIFSIGNALED(last_status))
    {
        printf ("\n");
        return (128 + WTERMSIG(last_status));
    }
    return (1);
}

int execute_pipeline(t_cli *cli)
{
    t_cli *current;
    int prev_pipe;
    int pipe_fd[2];
    bool has_next;
    pid_t pid;
    pid_t last_pid;
    int num_cmds;
    pid_t *child_pids;
    int child_count;
    int exit_code;

    current = cli;
    prev_pipe = -1;
    last_pid = -1;
    child_count = 0;
    num_cmds = 0;
    for (t_cli *tmp = cli; tmp; tmp = tmp->next)
        num_cmds++;
    child_pids = calloc(num_cmds, sizeof(pid_t));
    if (!child_pids)
    {
        perror("calloc");
        return 1;
    }    
    ft_set_sig(IGNORE);
    if (ft_prepare_all_heredocs(cli) == -1)
        return (1);
    current = cli;
    while (current)
    {
        has_next = (current->next != NULL);
        if (has_next && pipe(pipe_fd) == -1)
            exit_perror("pipe");
        pid = fork();
        if (pid == -1)
            exit_perror("fork");
        if (pid == 0)
        {
            ft_set_sig(CHILD);
            if(has_next)
                setup_child(current, prev_pipe, pipe_fd);
            else
                setup_child(current, prev_pipe, NULL);
            exec_command(current);
        }
        child_pids[child_count++] = pid;
        if (prev_pipe != -1)
            close(prev_pipe);
        if (current->heredoc_fd != -1)
            close(current->heredoc_fd);
        if (has_next)
        {
            close(pipe_fd[1]);
            prev_pipe = pipe_fd[0];
        }
        else
        {
            prev_pipe = -1;
            last_pid = pid;
        }
        current = current->next;
    }
    ft_set_sig(IGNORE);
    exit_code = wait_for_children(last_pid, child_pids, child_count);
    ft_set_sig(PARENT);
    free(child_pids);
    return (exit_code);
}