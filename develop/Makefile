# Variables
CC        = gcc
CFLAGS    = -Wall -Wextra -Werror -g3
MLX_PATH  = mlx/
MLX_NAME  = libmlx.a
MLX       = $(MLX_PATH)$(MLX_NAME)
SRC       = main.c map_utils.c player_utils.c hook.c image.c textures.c ray.c fov.c math.c pixel.c wall.c input.c get_next_line.c get_input.c get_input_utils.c parser.c free.c moves.c moves_utils.c sleep.c
OBJ       = $(SRC:.c=.o)
OBJ_PATH  = ./objects/
OBJS      = $(addprefix $(OBJ_PATH), $(OBJ))
INC       = -I./mlx -I./
NAME      = cub3d

# Rules
all: $(OBJ_PATH) $(MLX) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(MLX) -lXext -lX11 -lm

$(MLX):
	make -sC $(MLX_PATH)

$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_PATH)
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(MLX_PATH) clean


re: fclean all

# Phony targets
.PHONY: all clean fclean re
