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
