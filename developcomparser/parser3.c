/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:10:09 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 20:10:10 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	tex_init(t_game *g)
{
	g->tex_values = malloc(sizeof(t_tex_flags));
	if (!g->tex_values)
		return ;
	ft_memset(g->tex_values, 0, sizeof(*(g->tex_values)));
	g->tex_values->no = NULL;
	g->tex_values->so = NULL;
	g->tex_values->we = NULL;
	g->tex_values->ea = NULL;
	g->tex_values->c = 0;
	g->tex_values->f = 0;
}

int	parser(char *input, t_game *g)
{
	if (input == NULL)
		return (1);
	tex_init(g);
	file_parser(input, g);
	return (0);
}

int	check_filename(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if (!(len <= 4 || ft_strncmp(file + len - 4, ".cub", 4)
			|| !ft_strncmp(file + len - 5, "/.cub", 5)))
		return (1);
	return (0);
}
