.SUFFIXES : .c .o

NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror
MEMORY = -g3 -fsanitize=address
LLDB = -g

RM = rm -f
INCLUDE = -I./mlx -I./libft -I./get_next_line -I./parse -I./matrix -I./vector -I./ray
LIBFT = libft/libft.a
MLX = mlx/libmlx.a
MLXFLAGS = -framework OpenGL -framework AppKit

SRCS = minirt.c \
	   mlx.c \
	   utils.c \
	   color.c \
	   parse/parse.c \
	   parse/gen_env.c \
	   parse/gen_objs.c \
	   parse/check_env.c \
	   parse/check_objs.c \
	   ray/ray.c \
	   get_next_line/get_next_line.c \
	   get_next_line/get_next_line_utils.c \
	   world2view.c \
	   vector/v_utils1.c \
	   vector/v_utils2.c \
	   vector/v_utils3.c \
	   vector/v_utils4.c \
	   matrix/m_utils1.c \
	   render.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(MLX):
	$(MAKE) -C ./mlx

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(MLXFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

clean:
	$(MAKE) clean -C ./mlx
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

mem:
	$(MAKE) fclean
	$(MAKE) mem -C ./libft
	$(MAKE) all CFLAGS="$(DEBUG)"

lldb:
	$(MAKE) fclean
	$(MAKE) lldb -C ./libft
	$(MAKE) all CFLAGS="$(LLDB)"

.PHONY: all clean fclean re mem lldb
