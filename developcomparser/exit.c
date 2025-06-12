/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte && gamado-x                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:15:40 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:47:42 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_pntr(void *mem)
{
	if (mem != NULL)
		free (mem);
	mem = NULL;
}

void	free_game(t_game *g)
{
	int	i;

	i = 0;
	if (!g)
		return ;
	free(g->mlx);
	free(g->tex_values->no);
	free(g->tex_values->so);
	free(g->tex_values->we);
	free(g->tex_values->ea);
	free(g->tex_values);
	free(g->map_str);
	free(g->tex_path_in);
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
