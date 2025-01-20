# Variables
CC        = gcc
CFLAGS    = -Wall -Wextra -Werror -g3
MLX_PATH  = mlx/
MLX_NAME  = libmlx.a
MLX       = $(MLX_PATH)$(MLX_NAME)
SRC       = main.c map_utils.c player_utils.c
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
