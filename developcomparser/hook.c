/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte && gamado-x                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:40 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:49:56 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Set key as pressed
int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		game->keys[KEY_ESC] = 1;
	else if (keycode == 's')
		game->keys[KEY_BCK] = 1;
	else if (keycode == 'w')
		game->keys[KEY_FW] = 1;
	else if (keycode == 65361)
		game->keys[KEY_ROTATE_L] = 1;
	else if (keycode == 65363)
		game->keys[KEY_ROTATE_R] = 1;
	else if (keycode == 'a')
		game->keys[KEY_L] = 1;
	else if (keycode == 'd')
		game->keys[KEY_R] = 1;
	return (0);
}

//Set keys as release
int	key_release(int keycode, t_game *game)
{
	if (keycode == 65307)
		game->keys[KEY_ESC] = 0;
	else if (keycode == 's')
		game->keys[KEY_BCK] = 0;
	else if (keycode == 'w')
		game->keys[KEY_FW] = 0;
	else if (keycode == 65361)
		game->keys[KEY_ROTATE_L] = 0;
	else if (keycode == 65363)
		game->keys[KEY_ROTATE_R] = 0;
	else if (keycode == 'a')
		game->keys[KEY_L] = 0;
	else if (keycode == 'd')
		game->keys[KEY_R] = 0;
	return (0);
}

int	key_hook(t_game *game)
{
	if (game->keys[KEY_ESC])
		close_window(game);
	else if (game->keys[KEY_FW])
		move_forward(game->player, game->map);
	else if (game->keys[KEY_BCK])
		move_backward(game->player, game->map);
	else if (game->keys[KEY_ROTATE_L])
		game->player->dir += 1;
	else if (game->keys[KEY_ROTATE_R])
		game->player->dir -= 1;
	else if (game->keys[KEY_L])
		move_left(game->player, game->map);
	else if (game->keys[KEY_R])
		move_right(game->player, game->map);
	if (game->player->dir > 360)
		game->player->dir -= 360;
	else if (game->player->dir < 0)
		game->player->dir += 360;
	ft_build_fov(game->player, game->map);
	mlx_clear_window(game->mlx, game->win);
	draw_window(game, game->player);
	return (0);
}
