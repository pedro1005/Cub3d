/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:52:59 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:53:01 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	tex_and_coulors_ready(t_game *g)
{
	if (g->tex_values->nbr_of_coulors_set == 2
		&& g->tex_values->nbr_of_tex_set == 4)
		return (true);
	return (false);
}

static void	config_line_parser(t_game *g)
{
	int	tex_path_len;

	tex_path_len = ft_strlen(g->tex_path_in);
	if (!ft_strncmp(g->tex_path_in, "NO ", 3) && tex_path_len > 7)
		tex_parser(g, 'n');
	else if (!ft_strncmp(g->tex_path_in, "SO ", 3) && tex_path_len > 7)
		tex_parser(g, 's');
	else if (!ft_strncmp(g->tex_path_in, "WE ", 3) && tex_path_len > 7)
		tex_parser(g, 'w');
	else if (!ft_strncmp(g->tex_path_in, "EA ", 3) && tex_path_len > 7)
		tex_parser(g, 'e');
	else if (!ft_strncmp(g->tex_path_in, "F ", 2) && tex_path_len > 6)
		coulor_parser(g, 'f');
	else if (!ft_strncmp(g->tex_path_in, "C ", 2) && tex_path_len > 6)
		coulor_parser(g, 'c');
	else if (g->tex_path_in)
		ft_error_exit(g, "Invalid config\n");
}

void	parse_keys(t_game *g, char **temp, char **t_line)
{
	while (**temp == ' ')
		(*temp)++;
	g->tex_path_in = ft_strtrim(*temp, "\r\t");
	free(*t_line);
	*t_line = NULL;
	config_line_parser(g);
}
