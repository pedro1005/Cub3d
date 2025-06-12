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

void	set_pos(t_player *p, char *str)
{
	p->pos_x = 0;
	p->pos_y = 0;
	if (!str)
		return ;
	while (*str)
	{
		while (*str && *str != '-')
		{
			if (ft_isalpha(*str))
				return ;
			p->pos_x++;
			str++;
		}
		if (*str == '-')
			str++;
		p->pos_x = 0;
		p->pos_y++;
	}
}

void	ft_player_init(t_player *player, t_game *g)
{
	set_pos(player, g->map_str);
	player->virtual_x = player->pos_x * WALL_SIZE + (WALL_SIZE / 2);
	player->virtual_y = player->pos_y * WALL_SIZE + (WALL_SIZE / 2);
	player->last_hit = 0;
	ft_build_fov(player, g->map);
}
