/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte && gamado-x                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:40 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:49:26 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_insertion(int *matrix_row, char *line)
{
	char	**nbrs;
	int		i;

	nbrs = ft_split(line, ' ');
	i = 0;
	while (nbrs[i])
	{
		matrix_row[i] = ft_atoi(nbrs[i]);
		free(nbrs[i]);
		i++;
	}
	free(nbrs);
}

void	populate_map(char *str, t_game *g)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (*str)
	{
		while (*str && *str != '-')
		{
			if (*str == '1' || *str == ' ')
				g->map[y][x] = 1;
			else
				g->map[y][x] = 0;
			x++;
			str++;
		}
		if (*str == '-')
			str++;
		x = 0;
		y++;
	}
}
