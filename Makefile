SRC_FILES = ./src/main.c \
./src/mlx/init_mlx.c	\
./src/mlx/pixel_put.c	\
./src/raycast/draw_line_utils.c	\
./src/raycast/sprites.c	\
./src/raycast/draw_line.c	\
./src/raycast/door.c	\
./src/raycast/hooks.c	\
./src/raycast/mini_map.c	\
./src/raycast/movement.c	\
./src/raycast/main_raycasting.c	\
./src/raycast/floor.c	\
./src/raycast/door2.c	\
./src/raycast/dda.c	\
./src/raycast/hook_mouse.c	\
./src/raycast/walls.c	\
./src/raycast/sprites_utils.c	\
./src/exit_cub3d.c	\
./src/utils/array_utils.c	\
./src/utils/substr.c	\
./src/utils/strdup.c	\
./src/utils/set_map.c	\
./src/utils/camera_start.c	\
./src/utils/map_utils.c	\
./src/utils/skip_space.c	\
./src/utils/texture_reader.c	\
./src/utils/math_utils.c	\
./src/parsing/map_parser.c	\
./src/parsing/main_parser.c	\
./src/parsing/int_parser.c	\
./src/parsing/textures_parser.c	\
./src/parsing/floor_parser.c	\


INCLUDES = -I./includes -I./libft/includes -I./minilibx-linux

ifeq ($(where cc), 0)
  CC = cc
else ifeq ($(where clang), 0)
  CC = clang
else ifeq ($(where gcc), 0)
  CC = gcc
endif

OBJ_FILES = ${SRC_FILES:%.c=%.o}

FLAGS = -Wall -Werror -Wextra $(INCLUDES)

NAME = cub3D

MLX_FLAG = -lmlx -framework OpenGL -framework AppKit 

%.o : %.c
	@$(CC) $(FLAGS) -c $^ -o $@ $(OPTIMISATION)

all : linflag $(NAME)

WHITE_TEXT = \033[1;37m
RED_TEXT = \033[0;31m
NC_TEXT = \033[0m
GREEN_TEXT= \033[0;32m

./libft/libft.a :
	@echo "$(WHITE_TEXT)Archiving Libft..."
	@make -C ./libft

$(NAME) : $(OBJ_FILES) ./libft/libft.a
	@echo "$(WHITE_TEXT)Compiling Binary..."
	@$(CC) $(FLAGS) $^ $(MLX_FLAG) -o $(NAME) $(OPTIMISATION)
	@echo "$(GREEN_TEXT)	Success : $(NAME) Compiled Successfully"
	@echo "$(WHITE_TEXT)Finished"
	@echo "$(NC_TEXT)"

lin : linflag all

linflag : 
	$(eval MLX_FLAG := -lm -lmlx -lXext -lX11 -L./minilibx-linux)
	$(eval FLAGS = -Wall -Werror -Wextra $(INCLUDES) -DLINUX)

clean :
	@echo "$(RED_TEXT)Cleaning $(NAME) Object Files"
	@rm -rf	$(OBJ_FILES)
	@make -C ./libft clean
	@echo "$(NC_TEXT)"

fclean : clean
	@echo "$(RED_TEXT)Cleaning $(NAME) Binaries"
	@rm -rf $(NAME)
	@make -C ./libft fclean
	@echo "$(NC_TEXT)"

re : fclean all

bonus : all

.PHONY : clean fclean re all