/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:51:52 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:52:05 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	alloc_map_rows(t_game *g, int **map)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (i < g->map_rows)
	{
		map[i] = malloc((g->map_cols + 1) * sizeof(int));
		if (!map[i])
		{
			k = 0;
			while (k < i)
			{
				free(map[k]);
				k++;
			}
			free(map);
		}
		ft_memset(map[i], 0, (g->map_cols + 1) * sizeof(int));
		i++;
	}
	map[g->map_rows] = NULL;
}

int	**alloc_map(t_game *g)
{
	int		**map;

	map = NULL;
	map = malloc((g->map_rows + 1) * sizeof(int *));
	if (!map)
		return (NULL);
	alloc_map_rows(g, map);
	return (map);
}

void	free_map(int **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
