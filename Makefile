NAME = minishell

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

BONUS_OBJS = wildcard_bonus.o exec/ft_execute_bonus.o
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
    tokenizing/token_separator/handle_operator.c\
    tokenizing/token_separator/handle_escape_sequence.c\
    tokenizing/token_separator/handle_translation.c\
    tokenizing/token_separator/handle_quotes.c\
    tokenizing/token_separator/separator_utils.c\
    tokenizing/token_expansion/token_expansion.c\
    tokenizing/token_expansion/expansion_utils.c\
    tokenizing/token_error.c\
    tokenizing/token_finalize.c\
    parsing/parsing.c\
    parsing/parse_redir.c\
    parsing/parse_token.c\
    parsing/parse_heredoc.c\
    parsing/parse_pipe.c\
    parsing/parse_utils.c\
    signals/signals.c\
    signals/sig_manager.c\
    exec/exec_command.c\
    exec/exec_builtin.c\
    exec/exec_pipe.c\
    exec/builtins/ft_cd.c\
    exec/builtins/ft_echo.c\
    exec/builtins/ft_env.c\
    exec/builtins/ft_exit.c\
    exec/builtins/ft_export.c\
    exec/builtins/ft_pwd.c\
    exec/builtins/ft_unset.c\
    exec/exec_heredoc.c\
    exec/exec_utils.c\
    utils/utils.c\
    utils/utils1.c\
    utils/utils2.c\
    utils/loop_utils.c\
	wildcard_bonus.c

OBJ = $(SRC:.c=.o)

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

minishell_bonus: $(LIBFT_A) $(GNL_A) $(OBJ) exec/ft_execute_bonus.o
	cc $(CFLAGS) $(OBJ) exec/ft_execute_bonus.o $(LIBFT_A) $(GNL_A) -lreadline -o minishell_bonus

wildcard_bonus: wildcard_bonus.o
	cc $(CFLAGS) wildcard_bonus.o -o wildcard_bonus

wildcard_bonus.o: wildcard_bonus.c
	cc $(CFLAGS) -c wildcard_bonus.c -o wildcard_bonus.o

clean:
	rm -f $(OBJ) $(BONUS_OBJS) exec/ft_execute.o
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(GNL_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_BINS)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)

re: fclean all
