/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte && gamado-x                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:40 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:51:43 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_cols(t_game *g, char *line)
{
	if (ft_strlen(line) > (size_t)g->map_cols)
		g->map_cols = ft_strlen(line);
}

static void	get_data(t_game *g, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (!g->map_str)
		g->map_str = ft_strdup(line);
	else
	{
		tmp = ft_strjoin(g->map_str, "-");
		free(g->map_str);
		g->map_str = ft_strjoin(tmp, line);
		free(tmp);
	}
}

int	get_dir(char c)
{
	if (c == 'N')
		return (90);
	else if (c == 'S')
		return (270);
	else if (c == 'W')
		return (180);
	else if (c == 'E')
		return (360);
	return (1);
}

bool	val_map_set_player(t_game *g, char c)
{
	if (ft_strchr(" 01NSEW", c))
	{
		if (ft_isalpha(c))
		{
			if (g->player->dir != 0)
				return (false);
			g->player->dir = get_dir(c);
		}
		return (true);
	}
	return (false);
}

void	get_map(t_game *g, char *line)
{
	char	*t_line;

	t_line = line;
	if (g->map_rows > 0 && (line[0] != ' ' && line[0] != '1'))
	{
		free(line);
		ft_error_exit(g, "Invalid map\n");
	}
	while (*t_line)
	{
		if (!val_map_set_player(g, *t_line++))
		{
			free(line);
			ft_error_exit(g, "Invalid map\n");
		}
	}
	get_data(g, line);
	get_cols(g, line);
}
