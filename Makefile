NAME = miniRT

CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm -f

SRCS = minirt.c
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
	$(CC) $(CFLAGS) -c -o $@ $< -I libft -I mlx

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
