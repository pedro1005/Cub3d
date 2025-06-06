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
		printf( "Color or texture missing\n free g");
	printf( "Color or texture missing\n free g");
}

void    set_tex(t_game *g, char w, int i)
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

void    tex_parser(t_game *g, char wall)
{       
        int     fd_tex;
        int     i;

        if (tex_exists(g, wall))
                ft_error_exit(g, "Textura invalida");
        i = 3;
        while (g->tex_path_in[i] && ft_isspace(g->tex_path_in[i]))
                i++;
        if (!is_xpm_file(g, i))
                ft_error_exit(g, ".xpm invalido");
        fd_tex = open(g->tex_path_in + i, O_RDONLY);
        if (fd_tex < 0)
                ft_error_exit(g, "Textura invalida");
        close(fd_tex);
        set_tex(g, wall, i);
}

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
			ft_error_exit(g, "Invalid coulor. free g\n");
		while (g->tex_path_in[i] && ft_isdigit(g->tex_path_in[i]))
			rgb[j] = rgb[j] * 10 + (g->tex_path_in[i++] - 48);
		if (!is_valid_coulor(g, &i, j, rgb[j]))
			ft_error_exit(g, "Invalid coulor. free g\n");
		j++;
		if (j == 3 && g->tex_path_in[i])
			ft_error_exit(g, "Invalid color. free g\n");
	}
	if (j != 3)
		ft_error_exit(g, "Invalid color. free g\n");
	coulor_hexa(g, rgb, fc);
}

void    coulor_parser(t_game *g, char fc_coulor)
{
        int     i;

        if ((g->tex_values->c && fc_coulor == 'c') || (g->tex_values->f && fc_coulor == 'f'))
                printf("Coulor already defined");
        i = 2;
        while (g->tex_path_in[i] && ft_isspace(g->tex_path_in[i]))
                i++;
        rgb_parser(g, i, fc_coulor);
}