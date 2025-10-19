CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=$(BUFFER_SIZE)

NAME = get_next_line.a
SRC = get_next_line.c get_next_line_utils.c 
OBJ = $(SRC:.c=.o)
HEADER = get_next_line.h

BUFFER_SIZE ?= 42

all: $(NAME)

$(NAME):$(OBJ)
	ar rcs $(NAME) $(OBJ) 

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
