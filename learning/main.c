#include "cub3d.h"
#include "./mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Calcula a distância do raio (player -> parede)
float ft_get_ray_dist(double angle, t_player *player, int **map) {
    float dist = 0;
    float x_dist, y_dist;
    int temp_x = player->pos_x;
    int temp_y = player->pos_y;
    float temp_vx = player->virtual_x - (player->pos_x * WALL_SIZE);
    float temp_vy = player->virtual_y - (player->pos_y * WALL_SIZE);

    while (player->last_hit == 0)
    {
        double rad = angle * (M_PI / 180);
        if (angle > 0 && angle < 90) {
            // First quadrant: right and up
            y_dist = (WALL_SIZE - temp_vy) / sin(rad);
            x_dist = (WALL_SIZE - temp_vx) / cos(rad);
            if (y_dist < x_dist) {
                dist += y_dist;
                temp_y++;
                temp_vy = 0;
                temp_vx += y_dist * cos(rad);
                if (map[temp_y][temp_x] == 1) player->last_hit = N_DIR;
            } else {
                dist += x_dist;
                temp_x++;
                temp_vx = 0;
                temp_vy += x_dist * sin(rad);
                if (map[temp_y][temp_x] == 1) player->last_hit = E_DIR;
            }
        } else if (angle > 90 && angle < 180) {
            rad = (180 - angle) * (M_PI / 180);
            // Second quadrant: left and up
            y_dist = (WALL_SIZE - temp_vy) / sin(rad);
            x_dist = temp_vx / cos(rad);
            if (y_dist < x_dist) {
                dist += y_dist;
                temp_y++;
                temp_vy = 0;
                temp_vx -= y_dist * cos(rad);
                if (map[temp_y][temp_x] == 1) player->last_hit = N_DIR;
            } else {
                dist += x_dist;
                temp_x--;
                temp_vx = WALL_SIZE;
                temp_vy += x_dist * sin(rad);
                if (map[temp_y][temp_x] == 1) player->last_hit = W_DIR;
            }
        }
        else if (angle == 90)
        {
            rad = 90 * (M_PI / 180);
            y_dist = WALL_SIZE - temp_vy;
            dist = dist + y_dist;
            temp_y++;
            temp_vy = 0;
            if (map[temp_y][temp_x] == 1) player->last_hit = N_DIR;
        }
        else if (angle == 180)
        {
            rad = 180 * (M_PI / 180);
            x_dist = WALL_SIZE - temp_vx;
            dist = dist + x_dist;
            temp_x--;
            temp_vx = 0;
            if (map[temp_y][temp_x] == 1) player->last_hit = W_DIR;
        }
        else if (angle == 270)
        {
            rad = 270 * (M_PI / 180);
            y_dist = WALL_SIZE - temp_vy;
            dist = dist + y_dist;
            temp_y--;
            temp_vy = 0;
            if (map[temp_y][temp_x] == 1) player->last_hit = S_DIR;
        }
        else if (angle == 0 || angle == 360)
        {
            rad = 0;
            x_dist = WALL_SIZE - temp_vx;
            dist = dist + x_dist;
            temp_x++;
            temp_vx = 0;
            if (map[temp_y][temp_x] == 1) player->last_hit = E_DIR;
        }
        
        else if (angle > 180 && angle < 270) {
            // Third quadrant: left and down
           rad = (angle - 180) * (M_PI / 180);
        // Third quadrant: left and down
        y_dist = temp_vy / sin(rad);
        x_dist = temp_vx / cos(rad);
        if (y_dist < x_dist) {
            dist += y_dist;
            temp_y--;
            temp_vy = WALL_SIZE;
            temp_vx -= y_dist * cos(rad);
            if (map[temp_y][temp_x] == 1) player->last_hit = S_DIR;
        } else {
            dist += x_dist;
            temp_x--;
            temp_vx = WALL_SIZE;
            temp_vy -= x_dist * sin(rad);
            if (map[temp_y][temp_x] == 1) player->last_hit = W_DIR;
        }
        } else if (angle > 270 && angle < 360) {
            rad = (360 - angle) * (M_PI / 180);
        // Fourth quadrant: right and down
        y_dist = temp_vy / sin(rad);
        x_dist = (WALL_SIZE - temp_vx) / cos(rad);
        if (y_dist < x_dist) {
            dist += y_dist;
            temp_y--;
            temp_vy = WALL_SIZE;
            temp_vx += y_dist * cos(rad);
            if (map[temp_y][temp_x] == 1) player->last_hit = S_DIR;
        } else {
            dist += x_dist;
            temp_x++;
            temp_vx = 0;
            temp_vy -= x_dist * sin(rad);
            if (map[temp_y][temp_x] == 1) player->last_hit = E_DIR;
        }} else {
            return 0; // Invalid angle
        }
    }
    if (player->last_hit == N_DIR || player->last_hit == S_DIR) player->pos_hit = temp_vx;
    else
        player->pos_hit = temp_vy;
    return dist;
}


// Calcula as propriedades de um raio
t_fov ft_get_ray(double angle, t_player *player, int **map) {
    t_fov ray = {.dist = 0, .wall_texture = 0, .pos_hit = 0};
    //int dir = 0;

    if (angle > 360)
        angle -= 360;
    else if (angle < 0)
        angle += 360;
    //if (player->dir > angle)
    //    dir = player->dir - angle;
    //else if (player->dir < angle)
    //    dir = angle - player->dir;
    //ray.dist = ft_get_ray_dist(angle, player, map) * cos(dir * (M_PI / 180));
    ray.dist = ft_get_ray_dist(angle, player, map);

    ray.wall_texture = player->last_hit;
    ray.pos_hit = player->pos_hit;
    player->last_hit = 0;
    player->pos_hit = 0;

    return ray;
}

// Constrói o campo de visão do jogador
void ft_build_fov(t_player *player, int **map) {
    int i = 0;
    double angle = player->dir + (FOV_ANGLE / 2.0); // Abre o FOV a partir da direção do jogador
    double step = (double)FOV_ANGLE / (double)FOV_WIDTH;
    if (angle > 360) angle -= 360;

    while (i < FOV_WIDTH) {
        player->plane[i] = ft_get_ray(angle, player, map);
        angle -=step;
        if (angle < 0)
            angle += 360;
        if (angle > 360)
            angle -= 360;
        i++;
    }
}

// Inicializa o jogador
void ft_player_init(t_player *player, int **map) {
    player->pos_x = 1;
    player->pos_y = 5;
    player->dir = 70;
    player->virtual_x = player->pos_x * WALL_SIZE + (WALL_SIZE / 2);
    player->virtual_y = player->pos_y * WALL_SIZE + (WALL_SIZE / 2);
    player->last_hit = 0;
    ft_build_fov(player, map);
}

t_texture *load_texture(void *mlx, char *path) {
    t_texture *tex = malloc(sizeof(t_texture));
    if (!tex) return NULL;

    tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
    if (!tex->img) {
        free(tex);
        return NULL;
    }
    tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line, &tex->endian);
    return tex;
}

int get_pixel_color(t_texture *tex, int x, int y) {
    if (!tex || x < 0 || y < 0 || x >= tex->width || y >= tex->height) return 0x000000;
    return tex->data[y * (tex->size_line / 4) + x];
}

t_texture *get_texture(t_game *game, int texture_id) {
    if (texture_id == 2) return game->textures[0];
    if (texture_id == 3) return game->textures[1];
    if (texture_id == 4) return game->textures[2];
    if (texture_id == 5) return game->textures[3];
    return NULL;
}

void clear_image(t_game *game, int color)
{
    int x, y;
    char *pixel;

    for (y = 0; y < FOV_HEIGHT; y++)
    {
        for (x = 0; x < FOV_WIDTH; x++)
        {
            pixel = game->img.addr + (int)(y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
            *(unsigned int*)pixel = color;
        }
    }
}

// Interpolação suave com consideração da posição exata do impacto
int blend_colors(int color1, int color2, float weight)
{
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;

    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    int r = r1 + (r2 - r1) * weight;
    int g = g1 + (g2 - g1) * weight;
    int b = b1 + (b2 - b1) * weight;

    return (r << 16) | (g << 8) | b;
}
/*
void draw_rays(t_game *game, t_player *player)
{
    int i, y;
    int line_height, start_y, end_y;
    float corrected_distance;
    char *pixel;
    int wall_color;

    clear_image(game, 0x000000);  // Clear image before drawing
    printf("player->dir: %d\n", player->dir);

    for (i = 0; i < FOV_WIDTH; i++)
    {
       
        float angle_offset = (i - (FOV_WIDTH / 2)) * ((float)FOV_ANGLE / FOV_WIDTH);
        corrected_distance = player->plane[i].dist * cos(angle_offset * (M_PI / 180.0)); // Convert to radians

        if (corrected_distance < 0.01f) 
            corrected_distance = 0.01f; // Prevent division by zero

        line_height = (int)(FOV_HEIGHT * WALL_SIZE / corrected_distance);

        //line_height = (int)(FOV_HEIGHT * WALL_SIZE / distance);

        start_y = (FOV_HEIGHT - line_height) / 2;
        end_y = start_y + line_height;

        if (start_y < 0) start_y = 0;
        if (end_y >= FOV_HEIGHT) end_y = FOV_HEIGHT - 1;

        // Determine wall color based on wall_texture
        switch (player->plane[i].wall_texture) {
            case 5: wall_color = 0xFF0000; break; // Red
            case 2: wall_color = 0x0000FF; break; // Blue
            case 3: wall_color = 0x00FF00; break; // Green
            case 4: wall_color = 0xFFFF00; break; // Yellow
            default: wall_color = 0xFFFFFF; break; // White (fallback)
        }
        float shade_factor = 1.0f / (1.0f + corrected_distance * 0.05f);
        if (shade_factor < 0.7f) shade_factor = 0.7f;  // Prevent complete darkness

        // Adjust RGB values
        int r = ((wall_color >> 16) & 0xFF) * shade_factor;
        int g = ((wall_color >> 8) & 0xFF) * shade_factor;
        int b = (wall_color & 0xFF) * shade_factor;

        wall_color = (r << 16) | (g << 8) | b;

        // Draw solid color instead of texture
        for (y = start_y; y < end_y; y++)
        {
            pixel = game->img.addr + (y * game->img.line_length + i * (game->img.bits_per_pixel / 8));
            *(unsigned int*)pixel = wall_color;
        }
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}*/

void draw_rays(t_game *game, t_player *player) {
    int i, y;
    int line_height, start_y, end_y;
    int wall_color;
    t_texture *texture;
    int tex_x, tex_y;
    float tex_step, tex_pos;

    clear_image(game, 0x000000);  // Clear the screen

    for (i = 0; i < FOV_WIDTH; i++) {
    
        float angle_offset = (i - (FOV_WIDTH / 2)) * ((float)FOV_ANGLE / FOV_WIDTH);
        float corrected_distance = player->plane[i].dist * cos(angle_offset * (M_PI / 180.0)); // Convert to radians
        line_height = (int)(FOV_HEIGHT * WALL_SIZE / corrected_distance);

        start_y = (FOV_HEIGHT - line_height) / 2;
        end_y = start_y + line_height;
        if (start_y < 0) start_y = 0;
        if (end_y >= FOV_HEIGHT) end_y = FOV_HEIGHT - 1;

        // Get the appropriate texture
        texture = get_texture(game, player->plane[i].wall_texture);
        if (!texture) continue;

        // Determine texture X coordinate based on last_hit
       
            tex_x = (int)(player->plane[i].pos_hit * texture->width / WALL_SIZE);
      

        tex_x = tex_x % texture->width;  // Ensure within bounds

        // Vertical texture mapping
        tex_step = (float)texture->height / line_height;
        tex_pos = (start_y - FOV_HEIGHT / 2 + line_height / 2) * tex_step;

        for (y = start_y; y < end_y; y++) {
            tex_y = (int)tex_pos & (texture->height - 1);  // Wrap around texture height
            tex_pos += tex_step;

            wall_color = get_pixel_color(texture, tex_x, tex_y);

            // Draw the pixel
            char *pixel = game->img.addr + (y * game->img.line_length + i * (game->img.bits_per_pixel / 8));
            *(unsigned int *)pixel = wall_color;
        }
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}




int key_hook(int keycode, t_game *game) {
    t_player *player = &game->player;
    //int rad = player->dir * (M_PI / 180);

    if (keycode == 65307) { // Escape key
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    else if (keycode == 65362) { // Up arrow (move forward)
        player->virtual_y += STEP_SIZE;
        ft_build_fov(player, game->map);  // Recalculate FOV
        mlx_clear_window(game->mlx, game->win);
        draw_rays(game, player);
    }
    else if (keycode == 65364) { // Down arrow (move backward)
        player->virtual_y -= STEP_SIZE;
        ft_build_fov(player, game->map);  // Recalculate FOV
        mlx_clear_window(game->mlx, game->win);
        draw_rays(game, player);
    }
    else if (keycode == 65361) { // Left arrow (rotate left)
        player->dir += 5;
        if (player->dir < 0) player->dir += 360;
        ft_build_fov(player, game->map);  // Recalculate FOV
        mlx_clear_window(game->mlx, game->win);
        draw_rays(game, player);
    }
    else if (keycode == 65363) { // Right arrow (rotate right)
        player->dir -= 5;
        if (player->dir >= 360) player->dir -= 360;
        ft_build_fov(player, game->map);  // Recalculate FOV
        mlx_clear_window(game->mlx, game->win);
        draw_rays(game, player);
    }

    return 0;
}

int main() {
    t_game game;
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, FOV_WIDTH, FOV_HEIGHT, "Raycasting Test");
    game.img.ptr = mlx_new_image(game.mlx, FOV_WIDTH, FOV_HEIGHT);
    game.img.addr = mlx_get_data_addr(game.img.ptr, &game.img.bits_per_pixel,
                                       &game.img.line_length, &game.img.endian);
    game.textures[0] = load_texture(game.mlx, "./textures/42_EA.xpm");
    game.textures[1] = load_texture(game.mlx, "./textures/42_NO.xpm");
    game.textures[2] = load_texture(game.mlx, "./textures/42_SO.xpm");
    game.textures[3] = load_texture(game.mlx, "./textures/42_WE.xpm");

    
    int original_map[ROWS][COLS] = {
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1}
    };
    int **map = alloc_map(ROWS, COLS);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = original_map[i][j];
        }
    }

    t_player player;
    ft_player_init(&player, map);
    game.map = map;
    game.player = player;

    draw_rays(&game, &player);
    
    mlx_key_hook(game.win, key_hook, &game);

    mlx_loop(game.mlx);
    free_map(map, ROWS);
    return 0;
}
