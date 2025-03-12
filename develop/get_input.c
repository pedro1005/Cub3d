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

void    populate_map(char *input, int **map)
{
    int fd = open(input, O_RDONLY);
	int i = 0;
    char *line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map_insertion(map[i], line);
		free(line);
		i++;
	}
	close(fd);
}