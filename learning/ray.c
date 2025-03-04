#include "cub3d.h"

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
t_fov   ft_get_ray(double angle, t_player *player, int **map)
{
    t_fov ray = {.dist = 0, .wall_texture = 0, .pos_hit = 0};

    ray.dist = ft_get_ray_dist(angle, player, map);
    ray.wall_texture = player->last_hit;
    ray.pos_hit = player->pos_hit;
    player->last_hit = 0;
    player->pos_hit = 0;

    return (ray);
}