NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = r
RM = rm -f

SRCS = ft_putchar_fd.c \
	   ft_putendl_fd.c \
	   ft_putstr_fd.c \
	   ft_strchr.c \
	   ft_strncmp.c

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

.PHONY: clean fclean re all
