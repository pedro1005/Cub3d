#include "cub3d.h"

t_texture   *load_texture(void *mlx, char *path)
{
    t_texture   *tex;
    
    tex = malloc(sizeof(t_texture));
    if (!tex)
        return (NULL);
    tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        free(tex);
        return (NULL);
    }
    tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line, &tex->endian);
    return (tex);
}

t_texture *get_texture(t_game *game, int texture_id)
{
    if (texture_id == 2) return game->textures[0];
    if (texture_id == 3) return game->textures[1];
    if (texture_id == 4) return game->textures[2];
    if (texture_id == 5) return game->textures[3];
    return NULL;
}