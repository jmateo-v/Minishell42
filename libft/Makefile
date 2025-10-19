NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC := $(wildcard *.c)
OBJ = $(SRC:.c=.o)
INCLUDE = ftlib.h
AR = ar rcs
RM = rm -f

.PHONY: all clean fclean name

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -o $@ $< 
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
