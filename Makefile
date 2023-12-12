NAME = miniRT

CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm -f

SRCS = minirt.c \
	   mlx.c \
	   utils.c \
	   parse/parse.c \
	   parse/gen_env.c \
	   parse/gen_objs.c \
	   get_next_line/get_next_line.c \
	   get_next_line/get_next_line_utils.c \
	   world2view.c \
	   vector/v_utils1.c \
	   vector/v_utils2.c \
	   vector/v_utils3.c \
	   vector/v_utils4.c \
	   matrix/m_utils1.c

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a
MLX = mlx/libmlx.a
MLXFLAGS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(MLXFLAGS)

$(LIBFT):
	cd libft && $(MAKE)

$(MLX):
	cd mlx && $(MAKE)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I libft -I mlx -I get_next_line -I matrix -I vector

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) .bonus
	cd libft && $(MAKE) $@
	cd mlx && $(MAKE) $@

fclean: clean
	$(RM) $(NAME)
	cd libft && $(MAKE) $@
	cd mlx && $(MAKE) $<

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re all
