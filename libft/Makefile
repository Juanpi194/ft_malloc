NAME = libft.a
FLAGS = -Wall -Wextra -Werror
INCLUDE = -I $(INC_FOLDER)
SRC_FOLDER = src
INC_FOLDER = inc
CC = cc

COLOR_RESET                     := \033[0m
COLOR_GRAY                      := \033[0;30m
COLOR_LIGHT_GRAY        := \033[1;30m
COLOR_RED                       := \033[0;31m
COLOR_GREEN                     := \033[0;32m
COLOR_LIGHT_GREEN       := \033[1;32m
COLOR_YELLOW            := \033[0;33m
COLOR_LIGHT_YELLOW      := \033[1;33m
COLOR_BLUE                      := \033[0;34m
COLOR_LIGHT_BLUE        := \033[1;34m
COLOR_MAGENTA           := \033[0;35m
COLOR_CYAN                      := \033[0;36m
COLOR_WHITE                     := \033[0;37m
BOLD                            := \033[1m
BOLD_OFF                        := \033[22m
UNDERLINE                       := \033[4m
UNDERLINE_OFF       := \033[24m

FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
PREFIX_FILES = $(addprefix $(SRC_FOLDER)/, $(FILES))

LIST_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			  ft_lstclear.c ft_lstiter.c ft_lstmap.c
PREFIX_LIST_FILES = $(addprefix $(SRC_FOLDER)/, $(LIST_FILES))

EXTRA_FILES = 	ft_atol.c ft_str_isdigit.c ft_isspace.c ft_print_args.c \
				ft_num_len.c ft_putunbr_fd.c ft_putlnbr_fd.c ft_putulnbr_fd.c \
				ft_putnbr_base_fd.c ft_putlnbr_base_fd.c
PREFIX_EXTRA_FILES = $(addprefix $(SRC_FOLDER)/, $(EXTRA_FILES))

FT_PRINTF_FOLDER = ft_printf
FT_PRINTF_FILES =	ft_printf.c write_utils_1.c write_utils_2.c
FT_PRINTF_PREFIXED_FILES = $(addprefix $(FT_PRINTF_FOLDER)/, $(FT_PRINTF_FILES))
PREFIX_FT_PRINTF_FILES = $(addprefix $(SRC_FOLDER)/, $(FT_PRINTF_PREFIXED_FILES))

GET_NEXT_LINE_FILES = get_next_line.c
PREFIX_GET_NEXT_LINE_FILES = $(addprefix $(SRC_FOLDER)/, $(GET_NEXT_LINE_FILES))

ALL_FILES = $(FILES) $(LIST_FILES) $(EXTRA_FILES) $(FT_PRINTF_PREFIXED_FILES) $(GET_NEXT_LINE_FILES)

PREFIX_ALL_FILES = $(addprefix $(SRC_FOLDER)/, $(ALL_FILES))

OBJECTS = $(PREFIX_ALL_FILES:.c=.o)

COLOR_GREEN := \033[0;32m
COLOR_RESET := \033[0m

all: $(NAME)
	@rm -rf $(OBJECTS)

$(NAME): $(OBJECTS)
	@echo "⚙️  Compiling ... ⚙️"
	@ar rcs $(NAME) $(OBJECTS)
	@echo "✅ $(COLOR_GREEN)$(NAME) was succesfully created!$(COLOR_RESET)"

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)
	@echo "🧹$(COLOR_GREEN)Clean succesfully done!$(COLOR_RESET)🧹"

fclean: clean
	@rm -rf $(NAME)
	@echo "🧹$(COLOR_GREEN)Full clean succesfully done!$(COLOR_RESET)🧹"

re: fclean all

help:
	@echo "------------------------------------------------------------"
	@echo "🛠  $(COLOR_GREEN)AVAILABLE COMMANDS$(COLOR_RESET)  🛠:\n"

	@echo "$(COLOR_LIGHT_YELLOW)$(NAME)$(COLOR_RESET)\t\tCompiles every file and creates the $(NAME).\n"

	@echo "$(COLOR_LIGHT_YELLOW)clean$(COLOR_RESET)\t\tRemoves every temporary file from the project.\n"

	@echo "$(COLOR_LIGHT_YELLOW)fclean$(COLOR_RESET)\t\tRemoves every temporary file from the project, $(UNDERLINE)including the compiled file $(NAME)$(UNDERLINE_OFF).\n"

	@echo "$(COLOR_LIGHT_YELLOW)re$(COLOR_RESET)\t\tExecutes the $(UNDERLINE)fclean$(UNDERLINE_OFF) command and then recreates the $(NAME) by executing the $(UNDERLINE)$(NAME)$(UNDERLINE_OFF) rule.\n"

	@echo "------------------------------------------------------------"

.PHONY: all clean fclean re

.DEFAULT_GOAL= all