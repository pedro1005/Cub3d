#include "cub3d.h"

int get_pixel_color(t_texture *tex, int x, int y) {
    if (!tex || x < 0 || y < 0 || x >= tex->width || y >= tex->height) return 0x000000;
    return tex->data[y * (tex->size_line / 4) + x];
}

void draw_rays(t_game *game, t_player *player) {
    int i, y;
    int line_height, start_y, end_y;
    int wall_color;
    t_texture *texture;
    int tex_x, tex_y;
    float tex_step, tex_pos;

    // Draw sky (light blue) and floor (dark gray)
    for (y = 0; y < FOV_HEIGHT / 2; y++) {
        for (i = 0; i < FOV_WIDTH; i++) {
            char *pixel = game->img.addr + (y * game->img.line_length + i * (game->img.bits_per_pixel / 8));
            *(unsigned int *)pixel = 0x87CEEB;  // Sky color (light blue)
        }
    }
    for (y = FOV_HEIGHT / 2; y < FOV_HEIGHT; y++) {
        for (i = 0; i < FOV_WIDTH; i++) {
            char *pixel = game->img.addr + (y * game->img.line_length + i * (game->img.bits_per_pixel / 8));
            *(unsigned int *)pixel = 0x555555;  // Floor color (dark gray)
        }
    }

    // Draw walls
    for (i = 0; i < FOV_WIDTH; i++) {
        float angle_offset = (i - (FOV_WIDTH / 2)) * ((float)FOV_ANGLE / FOV_WIDTH);
        float corrected_distance = player->plane[i].dist * cos(angle_offset * (M_PI / 180.0)); 
        line_height = (int)(FOV_HEIGHT * WALL_SIZE / corrected_distance);

        start_y = (FOV_HEIGHT - line_height) / 2;
        end_y = start_y + line_height;
        if (start_y < 0) start_y = 0;
        if (end_y >= FOV_HEIGHT) end_y = FOV_HEIGHT - 1;

        texture = get_texture(game, player->plane[i].wall_texture);
        if (!texture) continue;

        tex_x = (int)(player->plane[i].pos_hit * texture->width / WALL_SIZE);
        tex_x = tex_x % texture->width;

        tex_step = (float)texture->height / line_height;
        tex_pos = fmax(0, (start_y - FOV_HEIGHT / 2 + line_height / 2) * tex_step);  // Ensure tex_pos is non-negative

        for (y = start_y; y < end_y; y++) {
            tex_y = (int)tex_pos % texture->height;  // Use modulo to avoid overflow
            tex_pos += tex_step;

            wall_color = get_pixel_color(texture, tex_x, tex_y);

            char *pixel = game->img.addr + (y * game->img.line_length + i * (game->img.bits_per_pixel / 8));
            *(unsigned int *)pixel = wall_color;
        }
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}