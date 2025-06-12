/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte && gamado-x                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:40 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:51:12 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_bounds(t_game *g, char el)
{
	if (el != '1' && el != ' ')
		ft_error_exit(g, "Map isn´t bounded\n");
}

static bool	is_bounded(t_game *g, size_t col, size_t row)
{
	char	**map;

	map = g->mapchar;
	if (col == 0 || col == (ft_strlen(map[row]) - 1) || row == 0 \
		|| row == (g->map_rows) - 1)
		return (true);
	else if (col >= ft_strlen(map[row - 1]) || col >= ft_strlen(map[row + 1]))
		return (true);
	return (false);
}

static void	validate_player_sur(t_game *g, char **map, size_t col, size_t row)
{
	if ((map[row - 1][col - 1] == '1' && map[row - 1][col] == '1' \
	&& map[row - 1][col + 1] == '1' && map[row][col - 1] == '1' \
	&& map[row][col + 1] == '1' && map[row + 1][col - 1] == '1' \
	&& map[row + 1][col] == '1' && map[row + 1][col + 1] == '1') || \
	(map[row - 1][col - 1] == ' ' && map[row - 1][col] == ' ' \
	&& map[row - 1][col + 1] == ' ' && map[row][col - 1] == ' ' \
	&& map[row][col + 1] == ' ' && map[row + 1][col - 1] == ' ' \
	&& map[row + 1][col] == ' ' && map[row + 1][col + 1] == ' '))
		ft_error_exit(g, "Locked player\n");
}

static void	validate_map_sur(t_game *g, char **map, size_t col, size_t row)
{
	if (map[row][col] == ' ')
	{
		if ((map[row - 1][col - 1] && !ft_strchr(" 1", map[row - 1][col - 1])) \
		|| (map[row - 1][col] && !ft_strchr(" 1", map[row - 1][col])) \
		|| (map[row - 1][col + 1] && !ft_strchr(" 1", map[row - 1][col + 1])) \
		|| (map[row][col - 1] && !ft_strchr(" 1", map[row][col - 1])) \
		|| (map[row][col + 1] && !ft_strchr(" 1", map[row][col + 1])) \
		|| (map[row + 1][col - 1] && !ft_strchr(" 1", map[row + 1][col - 1])) \
		|| (map[row + 1][col] && !ft_strchr(" 1", map[row + 1][col])) \
		|| (map[row + 1][col + 1] && !ft_strchr(" 1", map[row + 1][col + 1])))
			ft_error_exit(g, "Map invalid\n");
	}
	else if (map[row][col] == '0')
	{
		if (!ft_strchr("01SWNE", map[row - 1][col - 1]) || \
		!ft_strchr("01SWNE", map[row - 1][col]) \
		|| !ft_strchr("01SWNE", map[row - 1][col + 1]) \
		|| !ft_strchr("01SWNE", map[row][col - 1]) \
		|| !ft_strchr("01SWNE", map[row][col + 1]) \
		|| !ft_strchr("01SWNE", map[row + 1][col - 1]) \
		|| !ft_strchr("01SWNE", map[row + 1][col]) \
		|| !ft_strchr("01SWNE", map[row + 1][col + 1]))
			ft_error_exit(g, "Map invalid\n");
	}
}

void	map_validator(t_game *g)
{
    size_t     col;
	size_t     row;
	char	**map;

	map = g->mapchar;
	row = 0;
	while (row < g->map_rows)
	{
		col = 0;
		while (col < ft_strlen(map[row]))
		{
			if (is_bounded(g, col, row))
				check_bounds(g, map[row][col]);
			else if (!is_bounded(g, col, row) && ft_strchr("NSEW", map[row][col]))
				validate_player_sur(g, map, col, row);
			else if (!is_bounded(g, col, row) && ((map[row][col] == ' ') \
				|| (map[row][col] == '0')))
				validate_map_sur(g, map, col, row);
			col++;
		}
		row++;
	}
}
