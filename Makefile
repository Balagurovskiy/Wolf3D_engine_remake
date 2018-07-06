NAME = wolf3d

FILES =	main \
		map/map_utils \
		map/map_get_data \
		map/map_validation \
		raycaster/display \
		raycaster/raycast \
		raycaster/direction \
		raycaster/position \
		utils/xy \
		utils/window \
		utils/threads \
		utils/image
		
HDRS = includes/wolf.h

#add
SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))

FLAGS = -Wall -Wextra -Werror

FRAMEWORKS	=	-L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

HEADERS = -I./includes -I./libft/

all: lib $(NAME)

$(NAME): libft/libft.a $(OBJ)
	@gcc -o $(NAME) $(FLAGS) $(OBJ) $(FRAMEWORKS) libft/libft.a -g

libft/libft.a: lib

lib:
	@make -C ./libft/

$(OBJ): obj/%.o : src/%.c $(HDRS)
	@gcc -o $@ $(FLAG2) $(HEADERS) -c $<

clean:
	@rm -f $(OBJ)
	@make clean -C ./libft/

fclean :
	@rm -f $(NAME)
	@rm -rf $(OBJ)
	@make fclean -C ./libft/

re: fclean all
