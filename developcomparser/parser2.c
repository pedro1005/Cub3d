/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:08:59 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 20:09:02 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_emptyline(t_game *g, char **t_line)
{
	while (*t_line)
	{
		free(*t_line);
		*t_line = get_next_line(g->fd);
		if (*t_line && (*t_line[0] != '\n' && *t_line[0] != '\r'))
		{
			free(*t_line);
			ft_error_exit(g, "Empty line in map\n");
		}
	}
	free(*t_line);
}

static void	map_row_parser(t_game *g, char **line)
{
	if (((*line)[0] == ' ' || (*line)[0] == '1') && tex_and_coulors_ready(g))
	{
		get_map(g, *line);
		g->map_rows++;
	}
	else
	{
		free(*line);
		*line = NULL;
		missing_text_color(g);
	}
}

static void	lines_parser(t_game *g, char *t_line)
{
	char	*temp;

	temp = t_line;
	g->tex_path_in = NULL;
	if (ft_strchr(t_line, '.') || ft_strchr(t_line, ','))
		parse_keys(g, &temp, &t_line);
	if (g->tex_path_in)
		free (g->tex_path_in);
	else if (empty_line(t_line) && g->map_rows > 0)
	{
		parse_emptyline(g, &t_line);
		return ;
	}
	else if (!empty_line(t_line))
		map_row_parser(g, &t_line);
	free_pntr(t_line);
}

void	map_parser(t_game *g)
{
	if (!g->map_str)
		ft_error_exit(g, "File configuration error\n");
	g->mapchar = ft_split(g->map_str, '-');
	if (g->player->dir == 0)
		ft_exit(g, "Not initialized player\n", 0);
	map_validator(g);
}

void	file_parser(char *input, t_game *g)
{
	char	*line;
	char	*trimmed;

	g->fd = open(input, O_RDONLY);
	trimmed = NULL;
	if (g->fd < 0)
		close_window(g);
	line = get_next_line(g->fd);
	while (line)
	{
		trimmed = ft_strtrim(line, "\r\n");
		free(line);
		lines_parser(g, trimmed);
		line = get_next_line(g->fd);
	}
	map_parser(g);
}
