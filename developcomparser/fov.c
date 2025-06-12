/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte && gamado-x                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:40 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:48:20 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_build_fov(t_player *player, int **map)
{
	int		i;
	double	angle;
	double	step;

	i = 0;
	angle = player->dir + (FOV_ANGLE / 2.0);
	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;
	step = (double)FOV_ANGLE / (double)FOV_WIDTH;
	while (i < FOV_WIDTH)
	{
		player->plane[i] = ft_get_ray(angle, player, map);
		angle -= step;
		if (angle < 0)
			angle += 360;
		if (angle > 360)
			angle -= 360;
		i++;
	}
}
