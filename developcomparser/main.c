#include "cub3d.h"

void	ft_player_init(t_player *player, int **map)
{
	player->pos_x = 1;
	player->pos_y = 5;
	player->virtual_x = player->pos_x * WALL_SIZE + (WALL_SIZE / 2);
	player->virtual_y = player->pos_y * WALL_SIZE + (WALL_SIZE / 2);
	player->last_hit = 0;
	ft_build_fov(player, map);
}

void	clear_image(t_game *game, int color)
{
	int		x;
	int		y;
	char	*pixel;

	for (y = 0; y < FOV_HEIGHT; y++)
	{
		for (x = 0; x < FOV_WIDTH; x++)
		{
			pixel = game->img.addr + (int)(y * game->img.line_length
					+ x * (game->img.bits_per_pixel / 8));
			*(unsigned int *)pixel = color;
		}
	}
}

void	graph_handler(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, FOV_WIDTH, FOV_HEIGHT,
			"Raycasting Test");
	game->img.ptr = mlx_new_image(game->mlx, FOV_WIDTH, FOV_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	game->textures[0] = load_texture(game->mlx, game->tex_values->no);
	game->textures[1] = load_texture(game->mlx, game->tex_values->so);
	game->textures[2] = load_texture(game->mlx, game->tex_values->we);
	game->textures[3] = load_texture(game->mlx, game->tex_values->ea);
}

int	main(int ac, char **av)
{
	t_game		*game;
	t_player	*player;

	if (ac != 2 || !check_filename(av[1]))
	{
		printf("Error");
		return (1);
	}
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		exit(1);
	ft_memset(game, 0, sizeof(game));
	player = (t_player *)malloc(sizeof(t_player));
	game->player = player;
	if (!player)
		exit(1);
	parser(av[1], game);
	graph_handler(game);
	//get_map_size(av[1], game);
	game->map = alloc_map(game);
	populate_map(game->map_str,game);
	ft_player_init(player, game->map);
	memset(game->keys, 0, sizeof(game->keys));
	draw_window(game, game->player);
	mlx_hook(game->win, 2, 1L<<0, key_press, game);
    mlx_hook(game->win, 3, 1L<<1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
    mlx_loop_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
