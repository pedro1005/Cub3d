#include "cub3d.h"

// Inicializa o jogador
void    ft_player_init(t_player *player, int **map)
{
    player->pos_x = 1;
    player->pos_y = 5;
    player->dir = 70;
    player->virtual_x = player->pos_x * WALL_SIZE + (WALL_SIZE / 2);
    player->virtual_y = player->pos_y * WALL_SIZE + (WALL_SIZE / 2);
    player->last_hit = 0;
    ft_build_fov(player, map);
}

void clear_image(t_game *game, int color)
{
    int x, y;
    char *pixel;

    for (y = 0; y < FOV_HEIGHT; y++)
    {
        for (x = 0; x < FOV_WIDTH; x++)
        {
            pixel = game->img.addr + (int)(y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
            *(unsigned int*)pixel = color;
        }
    }
}


int main()
{
    t_game game;
    t_player player;

    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, FOV_WIDTH, FOV_HEIGHT, "Raycasting Test");
    game.img.ptr = mlx_new_image(game.mlx, FOV_WIDTH, FOV_HEIGHT);
    game.img.addr = mlx_get_data_addr(game.img.ptr, &game.img.bits_per_pixel,
                                       &game.img.line_length, &game.img.endian);
    game.textures[0] = load_texture(game.mlx, "./textures/paint.xpm");
    game.textures[1] = load_texture(game.mlx, "./textures/paint2.xpm");
    game.textures[2] = load_texture(game.mlx, "./textures/paint3.xpm");
    game.textures[3] = load_texture(game.mlx, "./textures/paint4.xpm");

    
    int original_map[ROWS][COLS] = {
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1}
    };
    int **map = alloc_map(ROWS, COLS);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = original_map[i][j];
        }
    }
    ft_player_init(&player, map);
    game.map = map;
    game.player = player;
    draw_window(&game, &game.player);
    mlx_key_hook(game.win, key_hook, &game);
    mlx_loop(game.mlx);
    free_map(map, ROWS);
    return 0;
}
