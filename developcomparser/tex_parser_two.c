/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_parser_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:00:24 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 20:00:28 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_coulor(t_game *g, int *i, int j, int color)
{
	if (color < 0 || color > 255)
		return (false);
	while (g->tex_path_in[*i] && ft_isspace(g->tex_path_in[*i]))
		(*i)++;
	if (j < 2 && g->tex_path_in[*i] != ',')
		return (false);
	else if (j < 2 && g->tex_path_in[*i] == ',')
		(*i)++;
	while (g->tex_path_in[*i] && ft_isspace(g->tex_path_in[*i]))
		(*i)++;
	if (j == 2 && g->tex_path_in[*i] && !ft_isspace(g->tex_path_in[*i]))
		return (false);
	return (true);
}

static void	coulor_hexa(t_game *g, int *rgb, char fc)
{
	int	coulor_hexa;

	coulor_hexa = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	if (fc == 'f')
	{
		g->tex_values->nbr_of_coulors_set += 1;
		g->tex_values->f_hexa = coulor_hexa;
	}
	else if (fc == 'c')
	{
		g->tex_values->nbr_of_coulors_set += 1;
		g->tex_values->c_hexa = coulor_hexa;
	}
	else
		ft_error_exit(g, "Invalid coulor. free cub\n");
}

static void	rgb_parser(t_game *g, int i, char fc)
{
	int	rgb[3];
	int	j;

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	j = 0;
	while (g->tex_path_in[i])
	{
		while (g->tex_path_in[i] && ft_isspace(g->tex_path_in[i]))
			i++;
		if (!ft_isdigit(g->tex_path_in[i]))
			ft_error_exit(g, "Invalid coulor\n");
		while (g->tex_path_in[i] && ft_isdigit(g->tex_path_in[i]))
			rgb[j] = rgb[j] * 10 + (g->tex_path_in[i++] - 48);
		if (!is_valid_coulor(g, &i, j, rgb[j]))
			ft_error_exit(g, "Invalid coulor\n");
		j++;
		if (j == 3 && g->tex_path_in[i])
			ft_error_exit(g, "Invalid color\n");
	}
	if (j != 3)
		ft_error_exit(g, "Invalid color\n");
	coulor_hexa(g, rgb, fc);
}

void	coulor_parser(t_game *g, char fc_coulor)
{
	int	i;

	if ((g->tex_values->c_hexa && fc_coulor == 'c')
		|| (g->tex_values->f_hexa && fc_coulor == 'f'))
	{
		printf("Error\nColor duplicated\n");
		close_window(g);
	}
	i = 2;
	while (g->tex_path_in[i] && ft_isspace(g->tex_path_in[i]))
		i++;
	rgb_parser(g, i, fc_coulor);
}
