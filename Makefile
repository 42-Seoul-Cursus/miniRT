.SUFFIXES : .c .o

NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror
MEMORY = -g3 -fsanitize=address
LLDB = -g

RM = rm -f
INCLUDE = -I./include -I./mlx -I./libft
LIBFT = libft/libft.a
MLX = mlx/libmlx.a
MLXFLAGS = -framework OpenGL -framework AppKit

SRC_DIR = src

SRCS = \
	main.c \
	parse/get_next_line/get_next_line.c \
	parse/get_next_line/get_next_line_utils.c \
	parse/check_env.c \
	parse/check_map.c \
	parse/check_objs.c \
	parse/check_utils.c \
	parse/gen_env.c \
	parse/gen_objs.c \
	parse/gen_objs_utils.c \
	parse/parse_utils.c \
	parse/parse.c \
	render/color.c \
	render/mlx.c \
	render/render.c \
	render/hook.c \
	render/world2view.c \
	ray/hit/hit_cylinder.c \
	ray/hit/hit_cone.c \
	ray/hit/hit_disk.c \
	ray/hit/hit_plane.c \
	ray/hit/hit_sphere.c \
	ray/hit/hit.c \
	ray/phong.c \
	ray/ray.c \
	utils/utils.c \
	utils/m_utils1.c \
	utils/m_utils2.c \
	utils/v_utils1.c \
	utils/v_utils2.c \
	utils/v_utils3.c \
	utils/v_utils4.c
OBJS = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(MLXFLAGS)

$(MLX):
	$(MAKE) -C ./mlx

$(LIBFT):
	$(MAKE) -C ./libft

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
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
	$(MAKE) all CFLAGS="$(MEMORY)"

lldb:
	$(MAKE) fclean
	$(MAKE) lldb -C ./libft
	$(MAKE) all CFLAGS="$(LLDB)"

.PHONY: all clean fclean re mem lldb
