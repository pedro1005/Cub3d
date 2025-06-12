/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:54:03 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 18:23:08 by gamado-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	tex_exists(t_game *g, char wall)
{
	if (wall == 's' && g->tex_values->so)
		return (true);
	else if (wall == 'n' && g->tex_values->no)
		return (true);
	else if (wall == 'w' && g->tex_values->we)
		return (true);
	else if (wall == 'e' && g->tex_values->ea)
		return (true);
	return (false);
}

static bool	is_xpm_file(t_game *g, int i)
{
	int	fnm_len;

	if (ft_strchr(g->tex_path_in, '/'))
	{
		while (g->tex_path_in[i] != '/')
			i++;
	}
	fnm_len = ft_strlen(g->tex_path_in) - i;
	if (fnm_len <= 4 || ft_strncmp(g->tex_path_in + i + fnm_len - 4, ".xpm", 4))
		return (false);
	return (true);
}

void	missing_text_color(t_game *g)
{
	close (g->fd);
	if (!tex_and_coulors_ready(g))
		return ;
}

void	set_tex(t_game *g, char w, int i)
{
	if (w == 'n')
	{
		if (!g->tex_values->no)
			g->tex_values->nbr_of_tex_set += 1;
		g->tex_values->no = ft_strdup(g->tex_path_in + i);
	}
	if (w == 's')
	{
		if (!g->tex_values->so)
			g->tex_values->nbr_of_tex_set += 1;
		g->tex_values->so = ft_strdup(g->tex_path_in + i);
	}
	if (w == 'w')
	{
		if (!g->tex_values->we)
			g->tex_values->nbr_of_tex_set += 1;
		g->tex_values->we = ft_strdup(g->tex_path_in + i);
	}
	if (w == 'e')
	{
		if (!g->tex_values->ea)
			g->tex_values->nbr_of_tex_set += 1;
		g->tex_values->ea = ft_strdup(g->tex_path_in + i);
	}
}

void	tex_parser(t_game *g, char wall)
{
	int	fd_tex;
	int	i;

	if (tex_exists(g, wall))
		ft_error_exit(g, "Duplicated texture\n");
	i = 3;
	while (g->tex_path_in[i] && ft_isspace(g->tex_path_in[i]))
		i++;
	if (!is_xpm_file(g, i))
		ft_error_exit(g, ".xpm invalido\n");
	fd_tex = open(g->tex_path_in + i, O_RDONLY);
	if (fd_tex < 0)
		ft_error_exit(g, "Invalid texture\n");
	close(fd_tex);
	set_tex(g, wall, i);
}
