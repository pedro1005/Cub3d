/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:54:17 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:54:22 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Loads a texture from an XPM file using the given mlx instance and file path.
t_texture	*load_texture(void *mlx, char *path)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		return (NULL);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		free(tex);
		return (NULL);
	}
	tex->data = (int *)mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->size_line, &tex->endian);
	return (tex);
}

// Returns a pointer to the requested texture based on its ID.
t_texture	*get_texture(t_game *game, int texture_id)
{
	if (texture_id == 2)
		return (game->textures[0]);
	if (texture_id == 3)
		return (game->textures[1]);
	if (texture_id == 4)
		return (game->textures[2]);
	if (texture_id == 5)
		return (game->textures[3]);
	return (NULL);
}
