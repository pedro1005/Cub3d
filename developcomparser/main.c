/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte && gamado-x                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:40 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:50:49 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pos(t_player *p, char *str)
{
	p->pos_x = 0;
	p->pos_y = 0;
	if (!str)
		return ;
	while (*str)
	{
		while (*str && *str != '-')
		{
			if (ft_isalpha(*str))
				return ;
			p->pos_x++;
			str++;
		}
		if (*str == '-')
			str++;
		p->pos_x = 0;
		p->pos_y++;
	}
}

void	ft_player_init(t_player *player, t_game *g)
{
	set_pos(player, g->map_str);
	player->virtual_x = player->pos_x * WALL_SIZE + (WALL_SIZE / 2);
	player->virtual_y = player->pos_y * WALL_SIZE + (WALL_SIZE / 2);
	player->last_hit = 0;
	ft_build_fov(player, g->map);
}

void	clear_image(t_game *game, int color)
{
	int		x;
	int		y;
	char	*pixel;

	y = 0;
	while (y < FOV_HEIGHT)
	{
		x = 0;
		while (x < FOV_WIDTH)
		{
			pixel = game->img.addr + (int)(y * game->img.line_length
					+ x * (game->img.bits_per_pixel / 8));
			*(unsigned int *)pixel = color;
			x++;
		}
		y++;
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

void	loop_hook(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
}

void	alloc_game(t_game **game)
{
	*game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		exit(1);
}

int	main(int ac, char **av)
{
	t_game		*game;
	t_player	*player;

	if (ac != 2 || !check_filename(av[1]))
	{
		printf("Error\nInvalid args\n");
		return (1);
	}
	game = NULL;
	alloc_game(&game);
	ft_memset(game, 0, sizeof(*game));
	player = (t_player *)malloc(sizeof(t_player));
	game->player = player;
	if (!player)
		exit(1);
	ft_memset(player, 0, sizeof(*player));
	parser(av[1], game);
	graph_handler(game);
	game->map = alloc_map(game);
	populate_map(game->map_str, game);
	ft_player_init(player, game);
	memset(game->keys, 0, sizeof(game->keys));
	draw_window(game, game->player);
	loop_hook(game);
	return (0);
}
