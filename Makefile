NAME = minishell

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

BONUS_OBJS = wildcard_match_bonus.o\
             wildcard_collect_bonus.o\
             wildcard_expand_bonus.o\
             wildcard_cli_bonus.o\
             wildcard_cli_count_bonus.o\
             wildcard_cli_fill_bonus.o\
             exec/ft_execute_bonus.o\
             tokenizing/token_error_bonus.o\
			 exec/ft_execute.o\
			 parsing/parsing_bonus.o\
			 parsing/parsing_redir_bonus.o\
			 parsing/parsing_logic_bonus.o\
			exec/ft_execute_helpers_bonus.o\
			tokenizing/handle_redirection_bonus.o

BONUS_BINS = minishell_bonus

GNL_DIR = get_next_line
GNL_A = $(GNL_DIR)/get_next_line.a
GNL_HEADER = -I$(GNL_DIR)

SRC = minishell.c\
    shell_helpers.c\
    shell_loop.c\
    shell_env.c\
    tokenizing/tokenizer.c\
    tokenizing/token_prep.c\
    tokenizing/token_separator/token_separator.c\
    tokenizing/token_separator/separator_loop.c\
    tokenizing/token_separator/handle_operator.c\
    tokenizing/token_separator/handle_escape_sequence.c\
    tokenizing/token_separator/handle_translation.c\
    tokenizing/token_separator/handle_quotes.c\
    tokenizing/token_separator/separator_utils.c\
    tokenizing/token_separator/separator_helpers.c\
    tokenizing/token_separator/separator_helpers1.c\
    tokenizing/token_expansion/token_expansion.c\
    tokenizing/token_expansion/expansion_utils.c\
    tokenizing/token_expansion/expand_segment.c\
    tokenizing/token_expansion/expand_token_seg.c\
    tokenizing/token_expansion/expansion_helpers.c\
    tokenizing/token_error.c\
    tokenizing/token_finalize.c\
    parsing/parsing.c\
    parsing/parse_redir.c\
    parsing/parse_token.c\
    parsing/ft_read_heredoc.c\
    parsing/parse_heredoc.c\
    parsing/parse_pipe.c\
    parsing/parse_utils.c\
    parsing/parse_helpers.c\
    parsing/handle_heredoc.c\
    signals/signals.c\
    signals/sig_manager.c\
    exec/exec_command.c\
    exec/exec_builtin.c\
    exec/exec_pipe/exec_pipe.c\
    exec/exec_pipe/setup_child.c\
    exec/exec_pipe/pipe_command.c\
    exec/exec_pipe/wait_children.c\
    exec/exec_pipe/run_pipe_loop.c\
    exec/builtins/ft_cd.c\
    exec/builtins/ft_echo.c\
    exec/builtins/ft_env.c\
    exec/builtins/ft_exit.c\
    exec/builtins/ft_export.c\
    exec/builtins/ft_pwd.c\
    exec/builtins/ft_unset.c\
    exec/builtins/builtin_utils.c\
    exec/exec_heredoc/exec_heredoc.c\
    exec/exec_heredoc/expand_variables.c\
    exec/exec_heredoc/heredoc_script.c\
    exec/exec_heredoc/heredoc_int.c\
    exec/exec_utils.c\
    utils/utils.c\
    utils/utils1.c\
    wildcard_match_bonus.c\
    wildcard_collect_bonus.c\
    wildcard_expand_bonus.c\
    wildcard_cli_bonus.c\
    wildcard_cli_count_bonus.c\
    wildcard_cli_fill_bonus.c\
	parsing/parsing_redir_bonus.c\
	parsing/parsing_logic_bonus.c\
	exec/ft_execute_helpers_bonus.c\
	tokenizing/handle_redirection_bonus.c\
    utils/utils2.c\
    utils/utils3.c\
    utils/mem_utils.c\
    utils/mem_utils1.c\
    utils/loop_utils.c

OBJ = $(SRC:.c=.o)

CFLAGS += -g -I$(LIBFT_DIR) -Iinclude $(GNL_HEADER) -Wall -Wextra -Werror -fsanitize=address
CFLAGS += -g -I$(LIBFT_DIR) $(GNL_HEADER) -Wall -Wextra -Werror #-fsanitize=address

all: $(NAME)

$(NAME): $(LIBFT_A) $(GNL_A) $(OBJ) exec/ft_execute.o
	cc $(CFLAGS) $(OBJ) exec/ft_execute.o $(LIBFT_A) $(GNL_A) -lreadline -o $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL_A):
	$(MAKE) -C $(GNL_DIR)

%.o: %.c include/minishell_bonus.h
	cc $(CFLAGS) -c $< -o $@

bonus: $(BONUS_BINS)

parsing/parsing_bonus.o: parsing/parsing_bonus.c minishell.h
	cc $(CFLAGS) -c parsing/parsing_bonus.c -o parsing/parsing_bonus.o

tokenizing/token_error_bonus.o: tokenizing/token_error_bonus.c minishell.h
	cc $(CFLAGS) -c tokenizing/token_error_bonus.c -o tokenizing/token_error_bonus.o

minishell_bonus: $(LIBFT_A) $(GNL_A) $(OBJ) parsing/parsing_bonus.o exec/ft_execute_bonus.o tokenizing/token_error_bonus.o
	cc $(CFLAGS) $(filter-out parsing/parsing.o tokenizing/token_error.o,$(OBJ)) parsing/parsing_bonus.o tokenizing/token_error_bonus.o exec/ft_execute_bonus.o $(LIBFT_A) $(GNL_A) -lreadline -o minishell_bonus

clean:
	rm -f $(OBJ) $(BONUS_OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(GNL_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_BINS)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)

re: fclean all
