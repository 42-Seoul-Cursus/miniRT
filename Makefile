.SUFFIXES : .c .o

NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror
MEMORY = -g3 -fsanitize=address
LLDB = -g

RM = rm -f
INCLUDE = -I./include -I./src/mlx -I./src/libft
LIBFT = src/libft/libft.a
MLX = src/mlx/libmlx.a
MLXFLAGS = -framework OpenGL -framework AppKit

SRC_DIR = src

SRCS = main.c \
	   mlx.c \
	   utils.c \
	   color.c \
	   hit_sphere.c \
	   render.c \
	   world2view.c \
	   get_next_line/get_next_line.c \
	   get_next_line/get_next_line_utils.c \
	   matrix/m_utils1.c \
	   parse/parse.c \
	   parse/gen_env.c \
	   parse/gen_objs.c \
	   parse/check_env.c \
	   parse/check_objs.c \
	   ray/ray.c \
	   vector/v_utils1.c \
	   vector/v_utils2.c \
	   vector/v_utils3.c \
	   vector/v_utils4.c
OBJS = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(MLX):
	$(MAKE) -C $(SRC_DIR)/mlx

$(LIBFT):
	$(MAKE) -C $(SRC_DIR)/libft

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(MLXFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

clean:
	$(MAKE) clean -C $(SRC_DIR)/mlx
	$(MAKE) clean -C $(SRC_DIR)/libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(SRC_DIR)/libft
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

mem:
	$(MAKE) fclean
	$(MAKE) mem -C $(SRC_DIR)/libft
	$(MAKE) all CFLAGS="$(DEBUG)"

lldb:
	$(MAKE) fclean
	$(MAKE) lldb -C $(SRC_DIR)/libft
	$(MAKE) all CFLAGS="$(LLDB)"

.PHONY: all clean fclean re mem lldb
