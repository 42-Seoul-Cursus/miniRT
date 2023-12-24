.SUFFIXES : .c .o

NAME = miniRT
NAME_BONUS = miniRT_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
MEMORY = -g3 -fsanitize=address
LLDB = -g

RM = rm -f
LIBFT = libft/libft.a
MLX = mlx/libmlx.a
MLXFLAGS = -framework OpenGL -framework AppKit

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

SRC_DIR = ./src
BONUS_DIR = ./bonus
INCLUDE = -I./include -I./mlx -I./libft

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
BONUS_SRCS = \
	main_bonus.c \
	parse/get_next_line/get_next_line_bonus.c \
	parse/get_next_line/get_next_line_utils_bonus.c \
	parse/check_env_bonus.c \
	parse/check_map_bonus.c \
	parse/check_objs_bonus.c \
	parse/check_utils_bonus.c \
	parse/gen_env_bonus.c \
	parse/gen_objs_bonus.c \
	parse/gen_objs_utils_bonus.c \
	parse/parse_utils_bonus.c \
	parse/parse_bonus.c \
	render/color_bonus.c \
	render/mlx_bonus.c \
	render/render_bonus.c \
	render/hook_bonus.c \
	render/world2view_bonus.c \
	ray/hit/hit_cylinder_bonus.c \
	ray/hit/hit_cone_bonus.c \
	ray/hit/hit_disk_bonus.c \
	ray/hit/hit_plane_bonus.c \
	ray/hit/hit_sphere_bonus.c \
	ray/hit/hit_bonus.c \
	ray/phong_bonus.c \
	ray/ray_bonus.c \
	utils/utils_bonus.c \
	utils/m_utils1_bonus.c \
	utils/m_utils2_bonus.c \
	utils/v_utils1_bonus.c \
	utils/v_utils2_bonus.c \
	utils/v_utils3_bonus.c \
	utils/v_utils4_bonus.c
BONUS_OBJS = $(addprefix $(BONUS_DIR)/, $(BONUS_SRCS:.c=.o))

ifdef WITH_BONUS
	OBJS = $(BONUS_OBJS)
endif

all: $(NAME)
	@echo "$(GREEN)$(NAME) created successfully$(RESET)"

bonus: 
	@$(MAKE) WITH_BONUS=1 all
	@echo "$(GREEN)Bonus part compiled successfully$(RESET)"

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(MLXFLAGS)
	@echo "$(WHITE)Creating $@$(RESET)"

$(MLX):
	@$(MAKE) all -C ./mlx
	@echo "$(GREEN)mlx compiled successfully$(RESET)"

$(LIBFT):
	@$(MAKE) all -C ./libft
	@echo "$(GREEN)libft compiled successfully$(RESET)"

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "$(CYAN)Compiled:$(RESET) $< -> $@"

$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "$(CYAN)Compiled Bonus:$(RESET) $< -> $@"

clean:
	@$(MAKE) clean -C ./mlx
	@$(MAKE) clean -C ./libft
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "$(BLUE)Cleaned up object files$(RESET)"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(NAME)
	@echo "$(BLUE)Cleaned up executable and library$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

mem:
	@$(MAKE) fclean
	@$(MAKE) mem -C ./libft
	@$(MAKE) all CFLAGS="$(MEMORY)"

lldb:
	@$(MAKE) fclean
	@$(MAKE) lldb -C ./libft
	@$(MAKE) all CFLAGS="$(LLDB)"

.PHONY: all clean fclean re mem lldb bonus
