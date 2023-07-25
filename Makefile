SRC_FILES = ${wildcard ./src/**/*.c} ${wildcard ./src/*.c} ${wildcard ./src/**/**/*.c}

INCLUDES = -I./includes -I./libft/includes

CC = cc

OBJ_FILES = ${SRC_FILES:%.c=%.o}

FLAGS = -Wall -Werror -Wextra $(INCLUDES) -fsanitize=address

NAME = cub3D

OPTIMISATION = -O2

MLX_FLAG = -lmlx -framework OpenGL -framework AppKit

%.o : %.c
	@$(CC) $(FLAGS) -c $^ -o $@ $(OPTIMISATION)

all : $(NAME)

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
	$(eval MLX_FLAG := -lm -lbsd -lmlx -lXext -lX11)
	$(eval FLAGS = -Wall -Werror -Wextra $(INCLUDES) -fsanitize=address -DLINUX)

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

.PHONY : clean fclean re all