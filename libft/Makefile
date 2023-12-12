.SUFFIXES : .c .o

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
MEMORY = -g3 -fsanitize=address
LLDB = -g
AR = ar
ARFLAGS = r
RM = rm -f

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

$(NAME): $(NAME)($(OBJS))

(%.o): %.c libft.h
	$(CC) $(CFLAGS) -c -o $% $<
	$(AR) $(ARFLAGS) $@ $%

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

mem:
	$(MAKE) all CFLAGS="$(CFLAGS) $(DEBUG)"

lldb:
	$(MAKE) all CFLAGS="$(CFLAGS) $(LLDB)"

.PHONY: clean fclean re all mem lldb
