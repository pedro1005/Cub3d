/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:52:33 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:52:36 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	*set_virt_xy(t_player *player, double rad)
{
	static float	virt_xy_i[2];

	virt_xy_i[0] = player->virtual_x - (player->pos_x * WALL_SIZE);
	virt_xy_i[1] = player->virtual_y - (player->pos_y * WALL_SIZE);
	virt_xy_i[0] = virt_xy_i[0] + STEP_SIZE * cos(rad);
	virt_xy_i[1] = virt_xy_i[1] + STEP_SIZE * sin(rad);
	return (virt_xy_i);
}

double	get_rad(int dir, int key)
{
	double	rad;

	rad = 0;
	if (key == KEY_R)
	{
		if (dir >= 90)
			rad = (dir - 90) * (M_PI / 180.0);
		else
			rad = (270 + dir) * (M_PI / 180.0);
	}
	else if (key == KEY_L)
	{
		if (dir <= 270)
			rad = (dir + 90) * (M_PI / 180.0);
		else
			rad = (dir - 270) * (M_PI / 180.0);
	}
	else if (key == KEY_BCK)
	{
		if (dir <= 180)
			rad = (dir + 180) * (M_PI / 180.0);
		else
			rad = (dir - 180) * (M_PI / 180.0);
	}
	return (rad);
}

int	check_x_collision(float virt_x, int **map, t_player *player)
{
	if (virt_x >= WALL_SIZE)
	{
		if (map[player->pos_y][player->pos_x + 1])
			return (1);
		player->pos_x += 1;
	}
	else if (virt_x <= 0)
	{
		if (map[player->pos_y][player->pos_x - 1])
			return (1);
		player->pos_x -= 1;
	}
	return (0);
}
