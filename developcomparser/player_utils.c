/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:53:25 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:53:31 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void    print_player(const t_player *player)
{
    printf("Player Position: (%d, %d)\n", player->pos_x, player->pos_y);
    printf("Direction: (%d)º\n", player->dir);
}
