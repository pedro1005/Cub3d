#include "cub3d.h"

void	move_right(t_player *player, int **map)
{
	float			*virt_xy_i;
	const double	rad = get_rad(player->dir, KEY_R);

	virt_xy_i = set_virt_xy(player, rad);
	if (check_x_colition(virt_xy_i[0], map, player))
		return ;
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

void	move_left(t_player *player, int **map)
{
	float			*virt_xy_i;
	const double	rad = get_rad(player->dir, KEY_L);

	virt_xy_i = set_virt_xy(player, rad);
	if (check_x_colition(virt_xy_i[0], map, player))
		return ;
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

void	move_backward(t_player *player, int **map)
{
	const float		*virt_xy_i;
	const double	rad = get_rad(player->dir, KEY_BCK);

	virt_xy_i = set_virt_xy(player, rad);
	if (check_x_colition(virt_xy_i[0], map, player))
		return ;
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

void	move_forward(t_player *player, int **map)
{
	const double	rad = player->dir * (M_PI / 180.0);
	const float		*virt_xy_i = set_virt_xy(player, rad);

	if (check_x_colition(virt_xy_i[0], map, player))
		return ;
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
