#include "cub3d.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int	g_texture = 0;

/*float	ft_get_xhip(float dir, float cathet)
{
	float	hip;
	float	rad;

	hip = 0;
	rad = dir * (M_PI / 180.0);
	hip = cathet / cos(rad);
	return (hip);
}

float	ft_get_yhip(float dir, float cathet)
{
	float	hip;
	float	rad;

	hip = 0;
	rad = dir * (M_PI / 180.0);
	hip = cathet / sin(rad);
	return (hip);
}

int	ft_get_ray_dist(int angle, t_player *player, int **map)
{
	int	dist;
	int	x_dist;
	int	y_dist;
	int	temp_x = player->pos_x;
	int	temp_y = player->pos_y;
	int	temp_vx = player->virtual_x - (player->pos_x * WALL_SIZE);
	int	temp_vy = player->virtual_y - (player->pos_y * WALL_SIZE);

	dist = 0;
	while (g_texture == 0)
	{
		if (angle >= 0 && angle <= 90)
		{
			y_dist = ft_get_yhip(angle, (WALL_SIZE - temp_vy));
			x_dist = ft_get_xhip(angle, (WALL_SIZE - temp_vx));
			if (y_dist < x_dist)
			{
				dist = dist + y_dist;
				temp_y++;
				temp_vy = temp_y * WALL_SIZE;
				temp_vx += (cos(angle * (M_PI / 180.0))) * y_dist;
				if (map[temp_y][temp_x] && map[temp_y][temp_x] == 1)
					g_texture = N_DIR;
			}
			else
			{
				dist = dist + x_dist;
				temp_x++;
				temp_vx = temp_x * WALL_SIZE;
				temp_vy += x_dist / (sin(angle * (M_PI / 180.0)));
				if (map[temp_y][temp_x] && map[temp_y][temp_x] == 1)
					g_texture = E_DIR;
			}
		}
		else
				return (0); // TODO: finish other quadrants
	}
	return (dist);
}

t_fov	ft_get_ray(float angle, t_player *player, int **map)
{
	t_fov	ray = {.dist = 0, .wall_texture = 0};

	ray.dist = ft_get_ray_dist(angle, player, map);
	ray.wall_texture = g_texture;
	g_texture = 0;

	return (ray);
}

void	ft_build_fov(t_player *player, int **map)
{
	int	i;
	int	angle;

	i = 0;
	angle = player->dir + 60;
	while (i < FOV_ANGLE)
	{
		player->plane[i] = ft_get_ray(angle, player, map);
		angle--;
		i++;
	}
}

void	ft_player_init(t_player *player, int **map)
{
	player->pos_x = 2;
	player->pos_y = 1;
	player->dir = 60;
	player->virtual_x = player->pos_x * WALL_SIZE + (WALL_SIZE / 2);
	player->virtual_y = player->pos_y * WALL_SIZE + (WALL_SIZE / 2);
	ft_build_fov(player, map);
}*/

// Calcula a hipotenusa baseada na direção e no cateto adjacente
float ft_get_xhip(float dir, float cathet)
{
    float rad = dir * (M_PI / 180.0);
    return (cathet / cos(rad));
}

// Calcula a hipotenusa baseada na direção e no cateto oposto
float ft_get_yhip(float dir, float cathet)
{
    float rad = dir * (M_PI / 180.0);
    return (cathet / sin(rad));
}

// Calcula a distância do raio (player -> parede)
int ft_get_ray_dist(int angle, t_player *player, int **map) {
    int dist = 0;
    float x_dist, y_dist;
    int temp_x = player->pos_x;
    int temp_y = player->pos_y;
    float temp_vx = player->virtual_x - (player->pos_x * WALL_SIZE);
    float temp_vy = player->virtual_y - (player->pos_y * WALL_SIZE);

    while (player->last_hit == 0)
    {
        if (angle < 0)
            angle += 360;
        double rad = angle * (M_PI / 180);
        if (angle >= 0 && angle <= 90) {
            // First quadrant: right and up
            y_dist = (WALL_SIZE - temp_vy) / sin(rad);
            x_dist = (WALL_SIZE - temp_vx) / cos(rad);
            if (y_dist < x_dist) {
                dist += y_dist;
                temp_y++;
                temp_vy = 0;
                temp_vx += y_dist / tan(rad);
                if (map[temp_y][temp_x] == 1) player->last_hit = N_DIR;
            } else {
                dist += x_dist;
                temp_x++;
                temp_vx = 0;
                temp_vy += x_dist * tan(rad);
                if (map[temp_y][temp_x] == 1) player->last_hit = E_DIR;
            }
        } else if (angle > 90 && angle <= 180) {
            rad = (180 - angle) * (M_PI / 180);
            // Second quadrant: left and up
            y_dist = (WALL_SIZE - temp_vy) / sin(rad);
            x_dist = temp_vx / cos(rad);
            if (y_dist < x_dist) {
                dist += y_dist;
                temp_y++;
                temp_vy = 0;
                temp_vx -= y_dist / tan(rad);
                if (map[temp_y][temp_x] == 1) player->last_hit = N_DIR;
            } else {
                dist += x_dist;
                temp_x--;
                temp_vx = WALL_SIZE;
                temp_vy += x_dist * tan(rad);
                if (map[temp_y][temp_x] == 1) player->last_hit = W_DIR;
            }
        } else if (angle > 180 && angle <= 270) {
            // Third quadrant: left and down
            y_dist = temp_vy / sin((angle - 180) * (M_PI / 180));
            x_dist = (WALL_SIZE - temp_vx) / cos((angle - 180) * (M_PI / 180));
            if (y_dist < x_dist) {
                dist += y_dist;
                temp_y--;
                temp_vy = 0;
                temp_vx -= cos((angle - 180) * (M_PI / 180)) * y_dist;
                if (map[temp_y][temp_x] == 1) player->last_hit = S_DIR;
            } else {
                dist += x_dist;
                temp_x--;
                temp_vx = WALL_SIZE;
                temp_vy -= (x_dist / sin((angle - 180) * (M_PI / 180)));
                if (map[temp_y][temp_x] == 1) player->last_hit = W_DIR;
            }
        } else if (angle > 270 && angle < 360) {
            // Fourth quadrant: right and down
            y_dist = temp_vy / sin((angle - 270) * (M_PI / 180));
            x_dist = (WALL_SIZE - temp_vx) / cos((angle - 270) * (M_PI / 180));
            if (y_dist < x_dist) {
                dist += y_dist;
                temp_y--;
                temp_vy = 0;
                temp_vx += cos((angle - 270) * (M_PI / 180)) * y_dist;
                if (map[temp_y][temp_x] == 1) player->last_hit = S_DIR;
            } else {
                dist += x_dist;
                temp_x++;
                temp_vx = 0;
                temp_vy -= (x_dist / sin((angle - 270) * (M_PI / 180)));
                if (map[temp_y][temp_x] == 1) player->last_hit = E_DIR;
            }
        } else {
            return 0; // Invalid angle
        }
    }
    return dist;
}


// Calcula as propriedades de um raio
t_fov ft_get_ray(float angle, t_player *player, int **map) {
    t_fov ray = {.dist = 0, .wall_texture = 0};
    double rad = 0;

    if (angle == player->dir)
        rad = angle * (M_PI / 180);
    else if (angle > player->dir)
        rad = (angle - player->dir) * (M_PI / 180);
    else
        rad = (player->dir - angle) * (M_PI / 180);
    ray.dist = ft_get_ray_dist(angle, player, map) * cos(rad);
    ray.wall_texture = player->last_hit;
    player->last_hit = 0;

    return ray;
}

// Constrói o campo de visão do jogador
void ft_build_fov(t_player *player, int **map) {
    int i = 0;
    int angle = player->dir + (FOV_ANGLE / 2); // Abre o FOV a partir da direção do jogador

    while (i < FOV_ANGLE) {
        player->plane[i] = ft_get_ray(angle, player, map);
        angle--;
        i++;
    }
}

// Inicializa o jogador
void ft_player_init(t_player *player, int **map) {
    player->pos_x = 2;
    player->pos_y = 2;
    player->dir = 60;
    player->virtual_x = player->pos_x * WALL_SIZE + (WALL_SIZE / 2);
    player->virtual_y = player->pos_y * WALL_SIZE + (WALL_SIZE / 2);
    player->last_hit = 0;
    ft_build_fov(player, map);
}

void draw_rays(t_game *game, t_player *player) {
    for (int i = 0; i < FOV_ANGLE; i++) {
        int line_height = player->plane[i].dist;
        int start_y = (320 - line_height) / 2; // Center the line vertically
        int end_y = start_y + line_height;

        // Calculate the x position of the ray
        int x = (i * 640) / FOV_ANGLE;

        // Determine the color based on the wall texture value
        int color;
        switch (player->plane[i].wall_texture) {
            case 2:
                color = 0x00FF00; // Green
                break;
            case 3:
                color = 0x0000FF; // Blue
                break;
            case 4:
                color = 0xFF0000; // Red
                break;
            case 5:
                color = 0xFFFF00; // Yellow
                break;
            default:
                color = 0xFFFFFF; // Default to white if no matching texture
                break;
        }

        // Draw the vertical line for the ray with the chosen color
        for (int y = start_y; y < end_y; y++) {
            mlx_pixel_put(game->mlx, game->win, x, y, color);
        }
    }
}

int key_hook(int keycode, t_game *game) {
    t_player *player = &game->player;
    if (keycode == 65307) { // Escape key
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    else if (keycode == 65362) { // Up arrow (move forward)
        player->pos_y++;
        ft_build_fov(player, game->map);  // Recalculate FOV
        mlx_clear_window(game->mlx, game->win);
        draw_rays(game, player);
    }
    else if (keycode == 65364) { // Down arrow (move backward)
        player->pos_y--;
        ft_build_fov(player, game->map);  // Recalculate FOV
        mlx_clear_window(game->mlx, game->win);
        draw_rays(game, player);
    }
    else if (keycode == 65361) { // Left arrow (rotate left)
        player->dir -= 5;
        if (player->dir < 0) player->dir += 360;
        ft_build_fov(player, game->map);  // Recalculate FOV
        mlx_clear_window(game->mlx, game->win);
        draw_rays(game, player);
    }
    else if (keycode == 65363) { // Right arrow (rotate right)
        player->dir += 5;
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
    game.win = mlx_new_window(game.mlx, 640, 320, "Raycasting Test");
    
    int original_map[ROWS][COLS] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
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




/*int main ()
{
	int original_map[ROWS][COLS] = {
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1}
	};
	int **map = alloc_map(ROWS, COLS);
	for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = original_map[i][j];
        }
    }
	
	t_player	player;
    t_game      game;

    game.mlx = mlx_init();

	ft_player_init(&player, map);
    game.win = mlx_new_window(game.mlx, 640, 320, "Raycasting Test");
    draw_rays(&game, &player);
     mlx_loop(game.mlx);
    free_map(map, ROWS);

	return 0;
}*/