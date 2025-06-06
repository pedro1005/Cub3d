#include "cub3d.h"

// Draws the sky in the upper half of the screen with the specified color.
void	draw_sky(t_game *game, int color)
{
	int		i;
	int		y;
	char	*pixel;

	i = 0;
	y = 0;
	pixel = NULL;
	while (y++ < FOV_HEIGHT / 2)
	{
		while (i < FOV_WIDTH)
		{
			pixel = game->img.addr
				+ (y * game->img.line_length
					+ i * (game->img.bits_per_pixel / 8));
			*(unsigned int *)pixel = color;
			i++;
		}
		i = 0;
	}
}

// Draws the floor in the lower half of the screen with the specified color.
void	draw_floor(t_game *game, int color)
{
	int		i;
	int		y;
	char	*pixel;

	i = 0;
	y = FOV_HEIGHT / 2;
	pixel = NULL;
	while (y++ < FOV_HEIGHT)
	{
		while (i < FOV_WIDTH)
		{
			pixel = game->img.addr
				+ (y * game->img.line_length
					+ i * (game->img.bits_per_pixel / 8));
			*(unsigned int *)pixel = color;
			i++;
		}
		i = 0;
	}
}

// Renders the entire game window by drawing the sky, floor, and walls.
void	draw_window(t_game *game, t_player *player)
{
	int			line_height;
	t_texture	*texture;
	t_wall_data	wall;
	int			x;

	x = 0;
	draw_sky(game, SKY_COLOR);
	draw_floor(game, FLOOR_COLOR);
	while (x < FOV_WIDTH)
	{
		line_height = get_line_height(x, player);
		texture = get_texture(game, player->plane[x].wall_texture);
		if (!texture)
			continue ;
		setup_wall_data(&wall, texture, player->plane[x].pos_hit, line_height);
		draw_wall_column(game, texture, x, &wall);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}
