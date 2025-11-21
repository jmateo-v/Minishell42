/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:29:38 by dogs              #+#    #+#             */
/*   Updated: 2025/11/21 11:57:41 by dansanc3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <sys/resource.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <errno.h>
# include <termios.h>

# define HERE_PIPE 3
# define HERE_DOC 2
# define IGNORE 2
# define PARENT 1
# define CHILD 0
# define READ 2
# define APPEND 1
# define WRITE 0
# define SEP_STR " \n\t<>|&()"
# define SEP_STR2 " \n\t<>|\"\'"
# define OP_STR "&|()"
# define OP_STR2 "&|"
# define PRNTS "()"
# define NO_OP 0
# define PIPE 1
# define AND 2
# define OR 3
# define IFS " \t\n"
# define REDIR_S "<>"
# define QUOTES "\"\'"
# define NO_VAL_VAR " !\"#$%&'()*+,-./:;<=>@[]^`{|}~ "
# define ERR_OPEN_Q "minishell: syntax error: quotes not closed\n"
# define ESC_CHARS1 "\\\"\?$"
# define PIPE_ERR "minishell: syntax error near unexpected token `|'\n"
# define UNEX_T1 "minishell: syntax error near unexpected token '<'\n"
# define UNEX_T2 "minishell: syntax error near unexpected token '>'\n"
# define HERE_ERR "minishell:here-document delimited by end-of-file (wanted `"
# define CMD_ERR ": command not found\n"
# define HERE_PIPE_ERR "minishell: syntax error: unexpected end of file\nexit\n"
# define SYN_ERR "minishell: syntax error near unexpected token `"
# define UNEX_EOF "minishell: syntax error: unexpected end of file\n"
# define ERR_NULL_TOKEN "minishell: internal error: null token\n"
# define ERR_EMPTY_TOKEN "minishell: internal error: empty token\n"
# define ERR_MISSING_REDIR_TARGET "minishell: syntax error: missing rd target"
# define MAX_CMDS 64
# define ERR_INVALID_ENV "minishell: env: failed to retrieve environment\n"
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern volatile sig_atomic_t	g_sig_rec;

typedef enum e_quote_state
{
	QSTATE_NONE,
	QSTATE_SINGLE,
	QSTATE_DOUBLE,
	QSTATE_ANSI_C
}	t_quote_state;

typedef enum e_seg_type
{
	QUOTE_NONE = 0,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_TRANSLATION,
	QUOTE_LITERAL,
	REDIRECTION,
	OPERATOR,
	OP_BRACKETS,
	CL_BRACKETS
}	t_seg_type;

typedef enum e_token_type
{
	T_WORD = 0,
	T_REDIRECTION,
	T_OPERATOR,
	T_OP_BRACKETS,
	T_CL_BRACKETS
}	t_token_type;

typedef struct s_segment
{
	char		*value;
	t_seg_type	type;
}	t_segment;

typedef struct s_token
{
	t_segment		*segments;
	char			*value;
	t_seg_type		seg_type;
	t_token_type	token_type;
}	t_token;

typedef struct s_separator_ctx
{
	t_seg_type	state;
	t_seg_type	current_type;
	char		buffer[1024];
	int			buf_i;
	int			token_i;
	int			seg_i;
	int			len;
	int			quote_state;
	t_token		*tokens;
	t_segment	*segments;
}	t_separator_ctx;

typedef struct s_shenv
{
	char			*var;
	struct s_shenv	*next;
}	t_shenv;

typedef struct s_heredoc
{
	char	*delimiter;
	bool	quoted;
	int		fd;
}	t_heredoc;

typedef struct s_cli
{
	char			*cmd;
	char			**args;
	char			*infile;
	char			*outfile;
	t_heredoc		*heredocs;
	int				num_heredocs;
	char			*s_heredoc;
	int				is_builtin;
	int				r_mode;
	t_shenv			**env;
	int				n_tokens;
	int				status;
	int				last_status;
	int				group;
	int				op;
	bool			breaks_pipe;
	struct s_cli	*next;
}	t_cli;

typedef struct s_pipe_state
{
	int	p[2];
	int	prev;
	int	i;
}	t_pipe_state;

typedef struct s_parse_ctx
{
	int		i;
	int		len;
	int		group;
	bool	in_heredoc;
	char	*heredoc_delim;
	bool	heredoc_quoted;
	t_cli	*heredoc_target;
}	t_parse_ctx;

bool	has_pipes_or_redirs(t_cli *cli);
char	**ft_expand_wildcard(char **token, int pos, int *wc_len);
t_token	*ft_token_sep(char *line);
char	**ft_insert_s_tokens(char **tokens);
char	**ft_lex_pipe(char **token, int *len);
t_token	*ft_expand_tokens(t_token *tokens, int *len, t_cli *cli);
t_token	*ft_tokenize_cl(char *line, t_cli *cli);
t_token	*ft_strip_quotes(t_token *tokens);
char	**ft_getshenv(t_shenv *env);
char	*ft_prompt(char **envp);
char	*get_hostname(void);
char	*get_pwd(char *cwd);
char	*ft_expand_line(char *token, t_cli *cli);
char	*ft_expand_var(const char *var, t_shenv *env, t_cli *cli);
char	*ft_get_var(char *var_call, char **envp);
char	*ft_escaped_line(char *line, int start, int end);
char	*ft_escape_quotes(char *line);
char	*ft_trim_delim(char *token, int *option);
char	*ft_expand_heredoc(int option, t_cli *cli);
char	*ft_cmd_path(char *env_path, char *cmd);
char	*ft_getenv(t_shenv *env, char *key);
char	*ft_expand_exit_status(int status, char *line, int i);
int		ft_heredoc_len(char *line);
int		ft_parse_token(t_token *token, int i, t_cli *cli, int *group);
int		ft_parse(t_token *tokens, t_cli *cli);
int		ft_export(char **args, t_shenv **env);
int		ft_unset(char **args, t_shenv **env);
int		ft_unsetenv(t_shenv **env, const char *key);
int		ft_check_errors(t_token *token, int len);
int		ft_pwd(char **args);
int		ft_echo(char **args);
int		ft_env(char **env);
int		ft_exit(char **args, int last_status);
int		ft_cd(char **args, t_shenv **env);
int		ft_setenv(t_shenv **env, char *key, char *value);
int		execute_command(t_cli *cli);
int		execute_builtin(t_cli *cmd);
int		ft_execute(t_cli *cli);
int		execute_pipeline(t_cli *cli);
int		ft_num_quoted(char *line);
int		ft_quoted_len(char *line, char quote);
int		shell_loop(t_cli *cli);
int		ft_num_s_tokens(char *line);
int		ft_precount_tokens(const char *line);
int		ft_var_len(char	*var);
int		ft_trim_s_len(char *line);
int		ft_append(char *token, t_cli *cli);
int		ft_heredoc(t_heredoc *hdoc, t_cli *cli);
int		ft_infile(char *token, t_cli *cli);
int		ft_outfile(char *token, t_cli *cli);
int		ft_cmd(char	*token, t_cli *cli);
int		ft_args(char *token, t_cli *cli, int pos);
int		ft_shenv_len(t_shenv *env);
void	ft_set_sig(int option);
int		init_separator_ctx(t_separator_ctx *ctx, char *line);
int		handle_escape_sequence(const char *line, int i, t_separator_ctx *ctx);
void	add_operator_token(char c, const char *line,
			int *i, t_separator_ctx *ctx);
void	handle_operator(char c, char *line, int *i, t_separator_ctx *ctx);
int		handle_translation(const char *line, int i, t_separator_ctx *ctx);
int		handle_quote_open(char c, t_separator_ctx *ctx);
void	handle_quote_close(char c, t_separator_ctx *ctx);
int		handle_ansi_c_quote(const char *line, int i, t_separator_ctx *ctx);
void	flush_segment(t_separator_ctx *ctx);
void	flush_token(t_separator_ctx *ctx);
void	flush_segment_with_type(t_separator_ctx *ctx, t_seg_type type);
void	ft_sig_parent(int signal);
void	ft_free_list(t_cli **cli);
void	ft_here_error(char *delim);
void	ft_free_tokens(t_token *tokens);
void	ft_perror(char *token, char *msg);
void	ft_free_env(t_shenv **env);
void	ft_reset_list(t_cli *cli);
t_cli	*ft_init_node(int len, t_shenv **envp, int op);
t_cli	*ft_parse_pipe(char *token, t_cli *cli);
t_shenv	*ft_load_env(char **envp);
void	ft_print_list(t_cli *cli);
char	*ft_trim_spaces(char *line);
int		ft_token_count(t_token *tokens);
void	ft_finalize_tokens(t_token *tokens);
int		ft_token_finalize(t_token *tok);
bool	is_directory(const char *path);
void	ft_free_str_array(char ***ptr);
char	*ft_strndup(const char *src, size_t n);
char	*ft_esc_str(char *s, char *esc_char, size_t n);
int		ft_isspace(int c);
size_t	ft_ptr_array_len(void **ptr);
char	**ft_add_str(char **dptr, const char *ptr, int pos);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_esc_line(char *line, int i, int len);
void	ft_cleanup_shell(t_cli **cli, t_shenv **env);
t_cli	*ft_setup_shell(char **envp, t_shenv **env);
int		ft_reset_signal(t_cli *cli);
void	ft_trunc(char *filename, t_cli *cli);
int		is_pipe(const char *s);
void	check_command_errors(t_cli *cmd);
int		ft_prepare_heredoc_fd(t_cli *cli);
int		ft_prepare_all_heredocs(t_cli *cli);
int		new_ft_check_errors(t_token *tokens, int n_tokens);
void	check_echoctl(void);
void	enable_echoctl(void);
int		ft_sig_hook(void);
char	*ft_read_with_hook(char *cl);
int		ft_check_signal(t_cli *cli);
int		ft_check_eof(char *cl);
void	ft_handle_command(char *cl, t_cli *cli);
char	*ft_read_input(void);
int		ft_process_command(char *cl, t_cli *cli);
void	ft_sig_int_parent(int sig);
void	setup_child(t_cli *cmd, int prev_pipe, int *pipe_fd);
void	exit_perror(const char *msg);
void	pipe_command(t_cli *cmd);
int		wait_for_children(pid_t last_pid, pid_t *child_pids, int child_count);
int		run_pipeline_loop(t_cli *cli, pid_t *pids, pid_t *last_pid);
int		handle_append_redirection(t_token *tokens,
			t_cli *cli, t_parse_ctx *ctx);
int		handle_append(t_token *tokens, t_cli *cli, t_parse_ctx *ctx);
int		handle_heredoc(t_token *tokens, t_cli *cli, t_parse_ctx *ctx);
int		handle_trunc(t_token *tokens, t_cli *cli, t_parse_ctx *ctx);
int		handle_infile(t_token *tokens, t_cli *cli, t_parse_ctx *ctx);
int		handle_pipe(t_token *tokens, t_cli **pcli, t_parse_ctx *ctx);
int		ft_read_heredoc(t_cli *cli, int *option, char *delim);
int		ft_script_heredoc(char *token, t_cli *cli);
char	*expand_variables(const char *input, t_shenv *env);
bool	is_quoted(const t_token *token);
void	heredoc_from_string(t_heredoc *hdoc, t_cli *cli, int write_fd);
void	heredoc_interactive(t_heredoc *hdoc, t_cli *cli, int write_fd);
int		handle_escape(char *line, int i, t_separator_ctx *ctx);
int		handle_operator_char(char c, char *line, int i, t_separator_ctx *ctx);
int		handle_translation_char(char *line, int i, t_separator_ctx *ctx);
int		handle_ansi_c_char(char *line, int i, t_separator_ctx *ctx);
int		handle_unquoted_char(char c, int i, t_separator_ctx *ctx);
int		handle_single_quote_char(char c, int i, t_separator_ctx *ctx);
int		handle_double_quote_char(char c, int i, t_separator_ctx *ctx);
char	*expand_segment(t_segment *seg, t_cli *cli, char *result);
char	*expand_token_segments(t_token *token, t_cli *cli);
int		sep_loop(char *line, t_separator_ctx *ctx);
void	parse_var_name(const char *seg_value, int *j, char *var, int var_size);
char	*exp_append_char(char *seg_expanded, char c, char *result);
void	cleanup(char *a, char *b, char *c, char *d);
t_token	*clean_err_return(char *line, t_segment *segments, t_token *tokens);
char	*append_literal_dollar(char *seg_expanded);
char	*append_var_value(char *seg_expanded, const char *var, t_cli *cli);
int		init_token_segments(t_token *token, const char *buffer);

#endif
