/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:54:29 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:54:33 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Calculates the height of a vertical wall slice to be drawn
//at a given screen column (x).
int	get_line_height(int x, t_player *player)
{
	const float	angle_offset = (x - (FOV_WIDTH / 2))
		* ((float)FOV_ANGLE / FOV_WIDTH);
	const float	corrected_distance = player->plane[x].dist
		* cos(angle_offset * (M_PI / 180.0));
	const int	line_height = (int)(FOV_HEIGHT
			* WALL_SIZE / corrected_distance);

	return (line_height);
}

// Draws a single vertical column of a wall texture at position x.
void	draw_wall_column(t_game *game, t_texture *texture,
	int x, t_wall_data *wall)
{
	float	tex_pos;
	int		y;
	int		tex_y;

	tex_pos = 0.0f;
	y = wall->start_y;
	tex_y = 0;
	if (wall->start_y == 0)
		tex_pos = (wall->line_height - FOV_HEIGHT) * 0.5f * wall->tex_step;
	while (y < wall->end_y)
	{
		tex_y = (int)tex_pos % texture->height;
		tex_pos += wall->tex_step;
		put_pixel(game, x, y, get_pixel_color(texture, wall->tex_x, tex_y));
		y++;
	}
}

// Prepares necessary wall rendering data before drawing a wall column.
void	setup_wall_data(t_wall_data *wall,
	t_texture *texture, float pos_hit, int line_height)
{
	wall->tex_x = (int)(pos_hit * texture->width / WALL_SIZE) % texture->width;
	wall->tex_step = (float)texture->height / line_height;
	wall->start_y = (FOV_HEIGHT - line_height) / 2;
	wall->end_y = wall->start_y + line_height;
	wall->line_height = line_height;
	if (wall->start_y < 0)
		wall->start_y = 0;
	if (wall->end_y > FOV_HEIGHT)
		wall->end_y = FOV_HEIGHT;
}
