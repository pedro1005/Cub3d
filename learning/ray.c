#include "cub3d.h"

// Calcula a distância do raio (player -> parede)
float	ft_get_ray_dist(double angle, t_player *player, int **map)
{
	float	dist;
	t_xypos	positions;

	dist = 0;
	positions.temp_xy[0] = player->pos_x;
	positions.temp_xy[1] = player->pos_y;
	positions.temp_v_xy[0] = player->virtual_x - (player->pos_x * WALL_SIZE);
	positions.temp_v_xy[1] = player->virtual_y - (player->pos_y * WALL_SIZE);
	while (player->last_hit == 0)
	{
		if (angle > 0 && angle < 90)
			dist += calc_q_one(angle, player, map, &positions);
		else if (angle > 90 && angle < 180)
			dist += calc_q_two(angle, player, map, &positions);
		else if (angle > 180 && angle < 270)
			dist += calc_q_three(angle, player, map, &positions);
		else if (angle > 270 && angle < 360)
			dist += calc_q_four(angle, player, map, &positions);
		else
			dist += calc_notables(angle, player, map, &positions);
	}
	player->pos_hit = positions.temp_v_xy[(player->last_hit != N_DIR
			&& player->last_hit != S_DIR)];
	return (dist);
}

// Calcula as propriedades de um raio
t_fov	ft_get_ray(double angle, t_player *player, int **map)
{
	t_fov	ray;

	ray.dist = ft_get_ray_dist(angle, player, map);
	ray.wall_texture = player->last_hit;
	ray.pos_hit = player->pos_hit;
	player->last_hit = 0;
	player->pos_hit = 0;
	return (ray);
}
