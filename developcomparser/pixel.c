/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:53:11 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:53:13 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Returns the color of a specific pixel from a texture at (x, y).
int	get_pixel_color(t_texture *tex, int x, int y)
{
	if (!tex || x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0x000000);
	return (tex->data[y * (tex->size_line / 4) + x]);
}

// Draws a pixel on the game screen at (x, y) with the given color.
void	put_pixel(t_game *game, int x, int y, int color)
{
	const char	*pixel = game->img.addr
		+ (y * game->img.line_length
			+ x * (game->img.bits_per_pixel / 8));

	*(unsigned int *)pixel = color;
}
