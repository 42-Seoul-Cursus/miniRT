.SUFFIXES : .c .o

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
MEMORY = -g3 -fsanitize=address
LLDB = -g
AR = ar
ARFLAGS = cr
RM = rm -f

BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
RESET = \033[0m

BLACK_ = \033[40m
RED_ = \033[41m
GREEN_ = \033[42m
YELLOW_ = \033[43m
BLUE_ = \033[44m
MAGENTA_ = \033[45m
CYAN_ = \033[46m
WHITE_ = \033[47m

INCLUDE = -I../include
SRCS = \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_error.c \
	ft_isdigit.c \
	ft_issign.c \
	ft_lstadd_back.c \
	ft_lstlast.c \
	ft_lstnew.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putstr_fd.c \
	ft_strchr.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strtod.c \
	ft_substr.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@echo "$(GREEN)$(NAME) created successfully$(RESET)"

$(NAME): $(OBJS)
	@echo "$(WHITE)Creating $@$(RESET)"
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "$(CYAN)Compiled:$(RESET) $< -> $@"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

mem:
	@$(MAKE) fclean
	@$(MAKE) all CFLAGS="$(CFLAGS) $(MEMORY)"

lldb:
	@$(MAKE) fclean
	@$(MAKE) all CFLAGS="$(CFLAGS) $(LLDB)"

.PHONY: clean fclean re all mem lldb
