#include "cub3d.h"

int get_xlen(int **map)
{
    int res;
    int i;

    res = 0;
    i = 0;
    if (!map)                           // Check if map is NULL
        return (0);
    while (map[i])                      // Iterate through the map while both map[i] and map[i][0] are valid
    {
        res++;
        i++;
    }
    return (res);
}

int get_ylen(int **map)
{
    int res;

    res = 0;
    if (!map || !map[0])
        return (0);
    while (map[0][res] != 0)           // Count elements in the first row (assuming map is properly alloc). This assumes all values are initialized, but it the bounds should be checked.
        res++;
    return (res);
}

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

void expand_map(int **new_map, int **map)
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int value = map[i][j];
            for (int r = i * WALL_SIZE; r < (i + 1) * WALL_SIZE; r++) {
                for (int c = j * WALL_SIZE; c < (j + 1) * WALL_SIZE; c++) {
                    new_map[r][c] = value;
                }
            }
        }
    }
}

void print_map(int **map, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == 5)
                printf(RED_COLOR "5 " RESET_COLOR);
            else
                printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

/*void enum_walls(int **map)
{
    int x;
    int y;

    if (!map)
        return;

    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x] != '\0') // Assuming '\0' marks the end of the row
        {
            if (map[y][x] == 1) // Only process if it's a wall
            {
                if (map[y + 1] && map[y + 1][x] == 0)
                    map[y][x] = S_WALL;
                else if (map[y][x + 1] && map[y][x + 1] == 0)
                    map[y][x] = E_WALL;
                else if (y > 0 && map[y - 1] && map[y - 1][x] == 0)
                    map[y][x] = N_WALL;
                else if (x > 0 && map[y][x - 1] == 0)
                    map[y][x] = W_WALL;
            }
            x++;
        }
        y++;
    }
}*/