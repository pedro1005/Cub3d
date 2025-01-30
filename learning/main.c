#include "cub3d.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Calcula a distância do raio (player -> parede)
int ft_get_ray_dist(int angle, t_player *player, int **map) {
    int dist = 0;
    int x_dist, y_dist;
    int temp_x = player->pos_x;
    int temp_y = player->pos_y;
    int temp_vx = player->virtual_x - (player->pos_x * WALL_SIZE);
    int temp_vy = player->virtual_y - (player->pos_y * WALL_SIZE);

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
    return dist;
}


// Calcula as propriedades de um raio
t_fov ft_get_ray(int angle, t_player *player, int **map) {
    t_fov ray = {.dist = 0, .wall_texture = 0};
    int dir = 0;

    if (angle > 360)
        angle -= 360;
    else if (angle < 0)
        angle += 360;
    if (player->dir > angle)
        dir = player->dir - angle;
    else if (player->dir < angle)
        dir = angle - player->dir;
    ray.dist = ft_get_ray_dist(angle, player, map) * cos(dir * (M_PI / 180));

    printf("angle: %d || dist: %d\n", angle, ray.dist);
    ray.wall_texture = player->last_hit;
    player->last_hit = 0;

    return ray;
}

// Constrói o campo de visão do jogador
void ft_build_fov(t_player *player, int **map) {
    int i = 0;
    int angle = player->dir + (FOV_ANGLE / 2); // Abre o FOV a partir da direção do jogador

    printf("START!\n");
    while (i < FOV_ANGLE) {
        player->plane[i] = ft_get_ray(angle, player, map);
        angle--;
        if (angle < 0)
            angle += 360;
        if (angle > 360)
            angle -= 360;
        i++;
    }
}

// Inicializa o jogador
void ft_player_init(t_player *player, int **map) {
    player->pos_x = 2;
    player->pos_y = 2;
    player->dir = 90;
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
    if (texture_id == 2) return game->textures[0];  // Exemplo: textura 2
    if (texture_id == 3) return game->textures[1];  // Exemplo: textura 3
    if (texture_id == 4) return game->textures[2];  // Exemplo: textura 4
    if (texture_id == 5) return game->textures[3];  // Exemplo: textura 5
    return NULL;
}



void draw_rays(t_game *game, t_player *player) {
    for (int i = 0; i < FOV_WIDTH; i++) {
        int x = (i * FOV_ANGLE) / FOV_WIDTH;
        float distance = player->plane[x].dist;

        if (distance < 0.1f) distance = 0.1f;

        int line_height = (int)(FOV_HEIGHT * WALL_SIZE / distance);
        int start_y = (FOV_HEIGHT - line_height) / 2;
        int end_y = start_y + line_height;

        if (start_y < 0) start_y = 0;
        if (end_y >= FOV_HEIGHT) end_y = FOV_HEIGHT - 1;

        // Obter a textura correta baseado no tipo da parede
        t_texture *tex = get_texture(game, player->plane[x].wall_texture);
        if (!tex) continue;

        // Coordenada X na textura (depende da posição do impacto)
        int tex_x = (int)(player->plane[x].wall_texture * tex->width) % tex->width;

        // Desenhar a parede com textura
        for (int y = start_y; y < end_y; y++) {
            int tex_y = ((y - start_y) * tex->height) / line_height;
            int color = get_pixel_color(tex, tex_x, tex_y);

            mlx_pixel_put(game->mlx, game->win, i, y, color);
        }
    }
    /*for (int i = 0; i < FOV_WIDTH; i++) {
        int x = ( i * FOV_ANGLE) / FOV_WIDTH;  // Supondo que FOV_WIDTH e o tamanho do array "plane" sejam equivalentes
        float distance = player->plane[x].dist;

        // Evita divisão por zero
        if (distance < 0.1f) distance = 0.1f;

        int line_height = (int)(FOV_HEIGHT * WALL_SIZE / distance); // Inverso da distância para efeito 3D
        int start_y = (FOV_HEIGHT - line_height) / 2;
        int end_y = start_y + line_height;

        // Limita os valores para não desenhar fora da tela
        if (start_y < 0) start_y = 0;
        if (end_y >= FOV_HEIGHT) end_y = FOV_HEIGHT - 1;

        // Determinar cor com base na textura do mapa
        int color;
        switch (player->plane[x].wall_texture) {
            case 2: color = 0x00FF00; break; // Verde
            case 3: color = 0x0000FF; break; // Azul
            case 4: color = 0xFF0000; break; // Vermelho
            case 5: color = 0xFFFF00; break; // Amarelo
            default: color = 0xFFFFFF; break; // Branco (padrão)
        }

        // Desenhar a linha vertical do raio
        for (int y = start_y; y < end_y; y++) {
            mlx_pixel_put(game->mlx, game->win, i, y, color);
        }
    }*/
}


int key_hook(int keycode, t_game *game) {
    t_player *player = &game->player;
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
    game.textures[0] = load_texture(game.mlx, "42_EA.xpm");
    game.textures[1] = load_texture(game.mlx, "42_NO.xpm");
    game.textures[2] = load_texture(game.mlx, "42_SO.xpm");
    game.textures[3] = load_texture(game.mlx, "42_WE.xpm");

    
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
