#include "cub3d.h"

float	calc_q_one(double angle, t_player *player, int **map, t_xypos *pos)
{
	float			xy_dist[2];
	const double	rad = angle * (M_PI / 180);

	xy_dist[1] = (WALL_SIZE - pos->temp_v_xy[1]) / sin(rad);
	xy_dist[0] = (WALL_SIZE - pos->temp_v_xy[0]) / cos(rad);
	if (xy_dist[1] < xy_dist[0])
	{
		pos->temp_xy[1]++;
		pos->temp_v_xy[1] = 0;
		pos->temp_v_xy[0] += xy_dist[1] * cos(rad);
		if (map[pos->temp_xy[1]][pos->temp_xy[0]] == 1)
			player->last_hit = N_DIR;
		return (xy_dist[1]);
	}
	else
	{
		pos->temp_xy[0]++;
		pos->temp_v_xy[0] = 0;
		pos->temp_v_xy[1] += xy_dist[0] * sin(rad);
		if (map[pos->temp_xy[1]][pos->temp_xy[0]] == 1)
			player->last_hit = E_DIR;
		return (xy_dist[0]);
	}
	return (0);
}

float	calc_q_two(double angle, t_player *player, int **map, t_xypos *pos)
{
	float			xy_dist[2];
	const double	rad = (180 - angle) * (M_PI / 180);

	xy_dist[1] = (WALL_SIZE - pos->temp_v_xy[1]) / sin(rad);
	xy_dist[0] = pos->temp_v_xy[0] / cos(rad);
	if (xy_dist[1] < xy_dist[0])
	{
		pos->temp_xy[1]++;
		pos->temp_v_xy[1] = 0;
		pos->temp_v_xy[0] -= xy_dist[1] * cos(rad);
		if (map[pos->temp_xy[1]][pos->temp_xy[0]] == 1)
			player->last_hit = N_DIR;
		return (xy_dist[1]);
	}
	else
	{
		pos->temp_xy[0]--;
		pos->temp_v_xy[0] = WALL_SIZE;
		pos->temp_v_xy[1] += xy_dist[0] * sin(rad);
		if (map[pos->temp_xy[1]][pos->temp_xy[0]] == 1)
			player->last_hit = W_DIR;
		return (xy_dist[0]);
	}
	return (0);
}

float	calc_q_three(double angle, t_player *player, int **map, t_xypos *pos)
{
	float			xy_dist[2];
	const double	rad = (angle - 180) * (M_PI / 180);

	xy_dist[1] = pos->temp_v_xy[1] / sin(rad);
	xy_dist[0] = pos->temp_v_xy[0] / cos(rad);
	if (xy_dist[1] < xy_dist[0])
	{
		pos->temp_xy[1]--;
		pos->temp_v_xy[1] = WALL_SIZE;
		pos->temp_v_xy[0] -= xy_dist[1] * cos(rad);
		if (map[pos->temp_xy[1]][pos->temp_xy[0]] == 1)
			player->last_hit = S_DIR;
		return (xy_dist[1]);
	}
	else
	{
		pos->temp_xy[0]--;
		pos->temp_v_xy[0] = WALL_SIZE;
		pos->temp_v_xy[1] -= xy_dist[0] * sin(rad);
		if (map[pos->temp_xy[1]][pos->temp_xy[0]] == 1)
			player->last_hit = W_DIR;
		return (xy_dist[0]);
	}
	return (0);
}

float	calc_q_four(double angle, t_player *player, int **map, t_xypos *pos)
{
	float			xy_dist[2];
	const double	rad = (360 - angle) * (M_PI / 180);

	xy_dist[1] = pos->temp_v_xy[1] / sin(rad);
	xy_dist[0] = (WALL_SIZE - pos->temp_v_xy[0]) / cos(rad);
	if (xy_dist[1] < xy_dist[0])
	{
		pos->temp_xy[1]--;
		pos->temp_v_xy[1] = WALL_SIZE;
		pos->temp_v_xy[0] += xy_dist[1] * cos(rad);
		if (map[pos->temp_xy[1]][pos->temp_xy[0]] == 1)
			player->last_hit = S_DIR;
		return (xy_dist[1]);
	}
	else
	{
		pos->temp_xy[0]++;
		pos->temp_v_xy[0] = 0;
		pos->temp_v_xy[1] -= xy_dist[0] * sin(rad);
		if (map[pos->temp_xy[1]][pos->temp_xy[0]] == 1)
			player->last_hit = E_DIR;
		return (xy_dist[0]);
	}
	return (0);
}

float	calc_notables(double angle, t_player *player, int **map, t_xypos *pos)
{
	float		dist;
	int			dir_index;
	const int	dx[] = {1, 0, -1, 0};
	const int	dy[] = {0, 1, 0, -1};
	const int	dirs[] = {E_DIR, N_DIR, W_DIR, S_DIR};

	dist = 0;
	dir_index = 0;
	if (angle == 360)
		angle = 0;
	dir_index = (int)(angle / 90);
	if (dir_index < 0 || dir_index > 3)
		return (0);
	dist = WALL_SIZE - pos->temp_v_xy[dir_index % 2];
	pos->temp_xy[0] += dx[dir_index];
	pos->temp_xy[1] += dy[dir_index];
	pos->temp_v_xy[dir_index % 2] = 0;
	if (map[pos->temp_xy[1]][pos->temp_xy[0]] == 1)
		player->last_hit = dirs[dir_index];
	return (dist);
}
