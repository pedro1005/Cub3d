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
        //printf("%s", g->tex_values->no);
}

bool	tex_and_coulors_ready(t_game *g)
{
	if (g->tex_values->nbr_of_coulors_set == 2 && g->tex_values->nbr_of_tex_set == 4)
		return (true);
	return (false);
}

static void map_row_parser(t_game *g, char **line)
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

static void     config_line_parser(t_game *g)
{
        int     tex_path_len;

        tex_path_len = ft_strlen(g->tex_path_in);
        if (!ft_strncmp(g->tex_path_in, "NO ", 3) && tex_path_len > 7)
                tex_parser(g, 'n');
        else if (!ft_strncmp(g->tex_path_in, "SO ", 3) && tex_path_len > 7)
                tex_parser(g,'s');
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

static void     lines_parser(t_game *g, char *t_line)
{
        g->tex_path_in = NULL;
        if (ft_strchr(t_line, '.') || ft_strchr(t_line, ','))
        {
                g->tex_path_in = ft_strtrim(t_line, "\r\t");
                free(t_line);
                t_line = NULL;
                config_line_parser(g);
        }
        if (g->tex_path_in)
                free (g->tex_path_in);
        else if (empty_line(t_line) && g->map_rows > 0)
        {
                free(t_line);
                ft_error_exit(g, "Empty line in input");
        }
        else if (!empty_line(t_line))
                map_row_parser(g, &t_line);
        free_pntr(t_line);
}

void	map_parser(t_game *g)
{
	if (!g->map_str)
		ft_error_exit(g, "Map error\n");
	g->mapchar = ft_split(g->map_str, '-');
	if (g->player->dir == 0)
		ft_exit(g, "Not initialized player\n", 0);
	map_validator(g);
}

void    file_parser(char *input, t_game *g)
{
        char    *line;
        char    *trimmed;

        g->fd = open(input, O_RDONLY);
        trimmed = NULL;
        if (g->fd < 0)
                //exit(1);
                close_window(g);
                //ft_exit(g, "File cannot be opened\n", 0);
        line = get_next_line(g->fd);
        while (line)
        {
                trimmed = ft_strtrim(line, "\r\n");
                free(line);
                lines_parser(g, trimmed);
                line = get_next_line(g->fd);
        }
        //valgrind p ver se o free do get_next_line foi feito
        map_parser(g);
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
	size_t len;

        len = ft_strlen(file);
        if (len < 4)
                return (0);
        if (!(len <= 4 || ft_strncmp(file + len - 4, ".cub", 4) || !ft_strncmp(file + len - 5, "/.cub", 5)))
                return (1);
        return (0);
}
