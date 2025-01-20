#include "cub3d.h"

int main ()
{
	int original_map[ROWS][COLS] = {
		{1, 1, 1, 1, 1},
		{1, 0, 0, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1}
	};
	int **new_map = alloc_map(ROWS * EXPAND_SIZE, COLS * EXPAND_SIZE);
	int **map = alloc_map(ROWS, COLS);
	for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = original_map[i][j];
        }
    }
	enum_walls(map);
	print_map(map, ROWS, COLS);
	expand_map(new_map,map);
	enum_walls(new_map);

	t_player	player = {
		.pos_x = (get_xlen(new_map) / 2) - 1 + (EXPAND_SIZE / 2),
		.pos_y = (get_ylen(new_map) / 2) - 1 - (EXPAND_SIZE / 2),
		.dir = 60
		};
	new_map[player.pos_y][player.pos_x] = 5;
	while (1)
	{
		if (!move_player(&player, new_map))
			break ;
	}
	print_map(new_map, ROWS * EXPAND_SIZE, COLS * EXPAND_SIZE);
	free_map(new_map, ROWS * EXPAND_SIZE);
    free_map(map, ROWS);

	return 0;
}