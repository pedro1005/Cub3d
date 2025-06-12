/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:51:52 by pedmonte          #+#    #+#             */
/*   Updated: 2025/06/12 17:52:05 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int **alloc_map(t_game *g)
{
    int **map = malloc((g->map_rows + 1) * sizeof(int *));         // Allocate space for `rows` pointers
    if (!map)
        return (NULL);
    for (size_t i = 0; i < g->map_rows; i++)
    {
        map[i] = malloc((g->map_cols + 1) * sizeof(int));
        if (!map[i])                                        // Free previously allocated rows if malloc fails
        {                              
            for (size_t k = 0; k < i; k++)
                free(map[k]);
            free(map);
            return (NULL);
        }
        memset(map[i], 0, (g->map_cols + 1) * sizeof(int));        // Initialize each row to 0
    }
    map[g->map_rows] = NULL;                                       // NULL terminate the array of pointers
    return (map);
}

void free_map(int **map, int rows)
{
    for (int i = 0; i < rows; i++)
        free(map[i]);
    free(map);
}

/*void print_map(int **map, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == 5)
                printf(RED_COLOR "5 " RESET_COLOR);
            else
                printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}*/
