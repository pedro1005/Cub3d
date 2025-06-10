#include "cub3d.h"


void	free_pntr(void *mem)
{
	if (mem != NULL)
		free (mem);
	mem = NULL;
}

void	free_game(t_game *g)
{
	if (!g)
		return ;
	free(g->mlx);
	//free(g->textures);
	/*if (g->map)
		free_map(g->map);*/
	free(g->tex_values->no);
	free(g->tex_values->so);
	free(g->tex_values->we);
	free(g->tex_values->ea);
	free(g->tex_values);
	free(g->map_str);
	free(g->tex_path_in);
	int i = 0;
	while (g->mapchar[i])
		free(g->mapchar[i++]);
	free(g->mapchar);
	get_next_line(-3);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
	}
}

void	ft_error_exit(t_game *g, char *msg)
{
	if (g->fd > 0)
		close (g->fd);
	ft_exit(g, msg, 0);
}

void	ft_exit(t_game *g, char *msg, int exitnbr)
{
    if (exitnbr == 0)
    {
        ft_putstr_fd("Error\n", (exitnbr + 1));
    }
    if (msg)
		ft_putstr_fd(msg, (exitnbr + 1));
    //free_game(g);
	close_window(g);
	exit (exitnbr);
}