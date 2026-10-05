# TODO: Must check the existence of the environment variable $HOSTTYPE
NAME = a.out

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -Ilibft/inc

INC_FOLDER = inc

LIBFT_FOLDER = libft
LIBFT_INC_FOLDER = $(LIBFT_FOLDER)/inc
LIBFT = libft/libft.a


SRCS = main.c \
		src/globals.c \
    	src/show_alloc_mem.c \
		src/zone_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

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