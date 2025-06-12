/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte && gamado-x                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:40 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:48:41 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (game->map && game->map[i])
		free(game->map[i++]);
	if (game->map)
		free(game->map);
	i = 0;
	while (i < 4 && game->textures[i])
	{
		free_texture(game->textures[i], game->mlx);
		i++;
	}
	free_pntr(game->tex_values->no);
	free_pntr(game->tex_values->so);
	free_pntr(game->tex_values->we);
	free_pntr(game->tex_values->ea);
	free_pntr(game->tex_values);
	free_pntr(game->map_str);
	free_pntr(game->tex_path_in);
	i = 0;
	while (game->mapchar && game->mapchar[i])
		free(game->mapchar[i++]);
	if (game->mapchar)
		free(game->mapchar);
	if (game->mlx)
	{
		mlx_destroy_image(game->mlx, game->img.ptr);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
	}
	free_pntr(game->player);
	
	free(game);
    exit(0);
	return (0);
}
