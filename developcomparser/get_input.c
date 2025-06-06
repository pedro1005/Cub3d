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

void    populate_map(char *str, t_game *g)
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
			printf("%d", g->map[y][x]);
			x++;
			str++;
		}
		if (*str == '-')
			str++;
		x = 0;
		y++;
		printf("\n");
	}

    
}