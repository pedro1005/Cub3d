#include "cub3d.h"

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
        if (player->dir > 360) player->dir -= 360;
        ft_build_fov(player, game->map);  // Recalculate FOV
        mlx_clear_window(game->mlx, game->win);
        draw_rays(game, player);
    }
    else if (keycode == 65363) { // Right arrow (rotate right)
        player->dir -= 5;
        if (player->dir < 0) player->dir += 360;
        ft_build_fov(player, game->map);  // Recalculate FOV
        mlx_clear_window(game->mlx, game->win);
        draw_rays(game, player);
    }

    return 0;
}