NAME = wolf3d

FILES =	main \
		map/map_utils \
		map/map_get_data \
		map/map_validation \
		map/map_border \
		raycaster/display \
		raycaster/raycast \
		raycaster/direction \
		raycaster/position \
		texture/txt_init \
		texture/txt_color \
		texture/txt_ray \
		texture/txt_draw \
		utils/xy \
		utils/window \
		utils/threads \
		utils/threads_image \
		utils/image
		
HDRS = includes/wolf.h

SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))

FLAGS = -Wall -Wextra -Werror

FRAMEWORKS = -L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

HEADERS = -I./includes -I./libft/

all: lib $(NAME)

$(NAME): libft/libft.a minilibx_macos/libmlx.a $(OBJ)
	@gcc -o $(NAME) $(FLAGS) $(OBJ) $(FRAMEWORKS) libft/libft.a -g

libft/libft.a: lib

lib:
	@make -C ./libft/
	@make -C ./minilibx_macos/

$(OBJ): obj/%.o : src/%.c $(HDRS)
	@gcc -o $@ $(FLAG2) $(HEADERS) -c $<

clean:
	@rm -f $(OBJ)
	@make clean -C ./libft/
	@make clean -C ./minilibx_macos/

fclean :
	@rm -f $(NAME)
	@rm -rf $(OBJ)
	@make fclean -C ./libft/
	@make clean -C ./minilibx_macos/

re: fclean all
