#include "cub3d.h"

//Set key as pressed
int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		game->keys[KEY_ESC] = 1;
	else if (keycode == 's')
		game->keys[KEY_BCK] = 1;
	else if (keycode == 'w')
		game->keys[KEY_FW] = 1;
	else if (keycode == 65361)
		game->keys[KEY_ROTATE_L] = 1;
	else if (keycode == 65363)
		game->keys[KEY_ROTATE_R] = 1;
	else if (keycode == 'a')
		game->keys[KEY_L] = 1;
	else if (keycode == 'd')
		game->keys[KEY_R] = 1;
	return (0);
}
//Set keys as release
int key_release(int keycode, t_game *game)
{
	if (keycode == 65307)
		game->keys[KEY_ESC] = 0;
	else if (keycode == 's')
		game->keys[KEY_BCK] = 0;
	else if (keycode == 'w')
		game->keys[KEY_FW] = 0;
	else if (keycode == 65361)
		game->keys[KEY_ROTATE_L] = 0;
	else if (keycode == 65363)
		game->keys[KEY_ROTATE_R] = 0;
	else if (keycode == 'a')
		game->keys[KEY_L] = 0;
	else if (keycode == 'd')
		game->keys[KEY_R] = 0;
	return (0);
}

float	*set_virt_xy(t_player *player, double rad)
{
	static float	virt_xy_i[2];

	virt_xy_i[0] = player->virtual_x - (player->pos_x * WALL_SIZE);
	virt_xy_i[1] = player->virtual_y - (player->pos_y * WALL_SIZE);
	virt_xy_i[0] = virt_xy_i[0] + STEP_SIZE * cos(rad);
	virt_xy_i[1] = virt_xy_i[1] + STEP_SIZE * sin(rad);

	return (virt_xy_i);
}

void    move_right(t_player *player, int **map)
{
	float	*virt_xy_i;
	double	rad;

	if (player->dir >= 90)
		rad = (player->dir - 90) * (M_PI / 180.0);
	else
		rad = (270 + player->dir) * (M_PI / 180.0);
	virt_xy_i = set_virt_xy(player, rad);
	if (virt_xy_i[0] >= WALL_SIZE)
	{
		if (map[player->pos_y][player->pos_x + 1])
			return ;
		player->pos_x += 1;
	}
	else if (virt_xy_i[0] <= 0)
	{
		if (map[player->pos_y][player->pos_x - 1])
			return ;
		player->pos_x -= 1;
	}
	player->virtual_x += STEP_SIZE * cos(rad);
	if (virt_xy_i[1] >= WALL_SIZE)
	{
		if (map[player->pos_y + 1][player->pos_x])
			return ;
		player->pos_y += 1;
	}
	else if (virt_xy_i[1] <= 0)
	{
		if (map[player->pos_y - 1][player->pos_x])
			return ;
		player->pos_y -= 1;
	}
	player->virtual_y += STEP_SIZE * sin(rad);
}

void    move_left(t_player *player, int **map)
{
	float	*virt_xy_i;
	double	rad;

	if (player->dir <= 270)
		rad = (player->dir + 90) * (M_PI / 180.0);
	else
		rad = (player->dir - 270) * (M_PI / 180.0);
	virt_xy_i = set_virt_xy(player, rad);
	if (virt_xy_i[0] >= WALL_SIZE)
	{
		if (map[player->pos_y][player->pos_x + 1])
			return ;
		player->pos_x += 1;
	}
	else if (virt_xy_i[0] <= 0)
	{
		if (map[player->pos_y][player->pos_x - 1])
			return ;
		player->pos_x -= 1;
	}
	player->virtual_x += STEP_SIZE * cos(rad);
	if (virt_xy_i[1] >= WALL_SIZE)
	{
		if (map[player->pos_y + 1][player->pos_x])
			return ;
		player->pos_y += 1;
	}
	else if (virt_xy_i[1] <= 0)
	{
		if (map[player->pos_y - 1][player->pos_x])
			return ;
		player->pos_y -= 1;
	}
	player->virtual_y += STEP_SIZE * sin(rad);
}

void    move_backward(t_player *player, int **map)
{
	const float		*virt_xy_i;
	double			rad;

	if (player->dir <= 180)
		rad = (player->dir + 180) * (M_PI / 180.0);
	else
		rad = (player->dir - 180) * (M_PI / 180.0);
	virt_xy_i = set_virt_xy(player, rad);
	if (virt_xy_i[0] >= WALL_SIZE)
	{
		if (map[player->pos_y][player->pos_x + 1])
			return ;
		player->pos_x += 1;
	}
	else if (virt_xy_i[0] <= 0)
	{
		if (map[player->pos_y][player->pos_x - 1])
			return ;
		player->pos_x -= 1;
	}
	player->virtual_x += STEP_SIZE * cos(rad);
	if (virt_xy_i[1] >= WALL_SIZE)
	{
		if (map[player->pos_y + 1][player->pos_x])
			return ;
		player->pos_y += 1;
	}
	else if (virt_xy_i[1] <= 0)
	{
		if (map[player->pos_y - 1][player->pos_x])
			return ;
		player->pos_y -= 1;
	}
	player->virtual_y += STEP_SIZE * sin(rad);
}

void    move_forward(t_player *player, int **map)
{
	const double	rad = player->dir * (M_PI / 180.0);
	const float		*virt_xy_i = set_virt_xy(player, rad);

	if (virt_xy_i[0] >= WALL_SIZE)
	{
		if (map[player->pos_y][player->pos_x + 1])
			return ;
		player->pos_x += 1;
	}
	else if (virt_xy_i[0] <= 0)
	{
		if (map[player->pos_y][player->pos_x - 1])
			return ;
		player->pos_x -= 1;
	}
	player->virtual_x += STEP_SIZE * cos(rad);
	if (virt_xy_i[1] >= WALL_SIZE)
	{
		if (map[player->pos_y + 1][player->pos_x])
			return ;
		player->pos_y += 1;
	}
	else if (virt_xy_i[1] <= 0)
	{
		if (map[player->pos_y - 1][player->pos_x])
			return ;
		player->pos_y -= 1;
	}
	player->virtual_y += STEP_SIZE * sin(rad);
}

void free_texture(t_texture *tex, void *mlx)
{
    if (tex)
    {
        if (tex->img)
            mlx_destroy_image(mlx, tex->img);
        free(tex);
    }
}

int close_window(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);
	i = 0;
	while (i < 4)
	{
		free_texture(game->textures[i], game->mlx);
		i++;
	}
	mlx_destroy_image(game->mlx, game->img.ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->player);
	mlx_loop_end(game->mlx);
	free(game->mlx);
	free(game);
    exit(0);
	return (0);
}

int key_hook(t_game *game)
{
	if (game->keys[KEY_ESC])
		close_window(game);
	else if (game->keys[KEY_FW])
		move_forward(game->player, game->map);
	else if (game->keys[KEY_BCK])
		move_backward(game->player, game->map);
	else if (game->keys[KEY_ROTATE_L])
	{
		game->player->dir += 1;
		if (game->player->dir > 360)
			game->player->dir -= 360;		
	}
	else if (game->keys[KEY_ROTATE_R])
	{
		game->player->dir -= 1;
		if (game->player->dir < 0)
			game->player->dir += 360;
	}
	else if (game->keys[KEY_L])
		move_left(game->player, game->map);
	else if (game->keys[KEY_R])
		move_right(game->player, game->map);
	ft_build_fov(game->player, game->map);
	mlx_clear_window(game->mlx, game->win);
	draw_window(game, game->player);
	return (0);
}
