/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:07:17 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 20:07:19 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(t_game *g, char *msg, int exitnbr)
{
	if (exitnbr == 0)
	{
		ft_putstr_fd("Error\n", (exitnbr + 1));
	}
	if (msg)
		ft_putstr_fd(msg, (exitnbr + 1));
	close_window(g);
	exit (exitnbr);
}
