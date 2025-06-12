/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte && gamado-x                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:40 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:50:19 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_nbr_counter(char *str, char c)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i])
			nbr++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	free(str);
	return (nbr);
}

int	get_rows(char *file_name)
{
	int		rows;
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (rows == 0)
		exit(0);
	return (rows);
}

int	get_cols(char *file_name)
{
	int	cols;
	int	fd;

	fd = open(file_name, O_RDONLY);
	cols = ft_nbr_counter(get_next_line(fd), ' ');
	close(fd);
	return (cols);
}

void	get_map_size(char *file_name, t_game *game)
{
	game->map_rows = get_rows(file_name);
	game->map_cols = get_cols(file_name);
}
