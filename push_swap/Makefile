NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
	init_prep/handle_errors.c \
	init_prep/init_a_to_b.c \
	init_prep/init_b_to_a.c \
	init_prep/split.c \
	init_prep/stack_init.c \
	init_prep/stack_utils.c \
	instructions/push.c \
	instructions/rev_rotate.c \
	instructions/rotate.c \
	sort/sort_stacks.c \
	sort/sort_three.c \
	sort/sort_utils.c \
	instructions/swap.c \
	sort/push_swap.c \

OBJS = $(SRCS:.c=.o)

LIBFT = libft.a

INCLUDES = -Iincludes

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
