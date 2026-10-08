# TODO: Must check the existence of the environment variable $HOSTTYPE
NAME = a.out

CC = gcc -g

# TODO: Add flags -Wall -Wextra -Werror
CFLAGS = -Iinc -Ilibft/inc

FSANITIZE_FLAG = -fsanitize=address

# TODO: Check with fsanitize
# TODO: Make rules to compile debug mode ...

INC_FOLDER = inc

LIBFT_FOLDER = libft
LIBFT_INC_FOLDER = $(LIBFT_FOLDER)/inc
LIBFT = libft/libft.a


SRCS = main.c \
		src/malloc/allocations.c \
		src/malloc/block_utils.c \
		src/malloc/ft_malloc.c \
		src/zones/link_zone.c \
		src/zones/zone_sizes.c \
		src/zones/zone_getters.c \
		src/globals.c \
    	src/show_alloc_mem.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_FOLDER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_FOLDER) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_FOLDER) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all $(LIBFT_FOLDER) clean fclean re