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

bool	val_map_set_player(t_game *g, char c)
{
	if (ft_strchr(" 01NSEW", c))
	{
		if (ft_isalpha(c))
		{
            //testar g->player->dir
			if (g->player->dir != 0)
				return (false);
			g->player->dir = c;
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