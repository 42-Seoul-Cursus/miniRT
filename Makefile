.SUFFIXES : .c .o

NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror
MEMORY = -g3 -fsanitize=address
LLDB = -g

RM = rm -f
INCLUDE = -I./include -I./src/mlx -I./src/libft
MLX = src/mlx/libmlx.a
MLXFLAGS = -framework OpenGL -framework AppKit

SRC_DIR = src

SRCS = \
	main.c \
	parse/get_next_line.c \
	parse/get_next_line_utils.c \
	minilibx/draw.c \
	minilibx/hook.c \
	minilibx/init.c \
	scene/canvas.c \
	scene/object_create.c \
	scene/scene.c \
	trace/ray/ray.c \
	trace/hit/hit_sphere.c \
	utils/vec3_utils.c

OBJS = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

ifneq "$(filter debugger, $(MAKECMDGOALS))" ""
	CFLAGS += $(LLDB)
endif

ifneq "$(filter sanitizer, $(MAKECMDGOALS))" ""
	CFLAGS += $(MEMORY)
endif

all: $(NAME)

$(MLX):
	$(MAKE) -C $(SRC_DIR)/mlx

$(NAME): $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(MLXFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

clean:
	$(MAKE) clean -C $(SRC_DIR)/mlx
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

mem:
	$(MAKE) fclean
	$(MAKE) sanitizer $(NAME)

lldb:
	$(MAKE) fclean
	$(MAKE) lldb -C $(SRC_DIR)/libft
	$(MAKE) debugger $(NAME)

.PHONY: all clean fclean re mem lldb debugger sanitizer
