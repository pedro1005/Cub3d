#ifndef CUB3D_H
# define CUB3D_H

#define ROWS 5
#define COLS 5
#define EXPAND_SIZE 30
#define STEP_SIZE 15
#define RED_COLOR "\033[31m"
#define RESET_COLOR "\033[0m"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_player
{
	int     pos_x;
	int     pos_y;
	float   dir;
	
} t_player;

typedef enum e_wall
{
	FLOOR,
	N_WALL,
	S_WALL,
	E_WALL,
	W_WALL,
	PLAYER_INIT
} t_wall;


//map_utils
void print_map(int **map, int rows, int cols);
void expand_map(int **new_map, int **map);
void free_map(int **map, int rows);
int **alloc_map(int rows, int cols);
int get_ylen(int **map);
int get_xlen(int **map);
void    enum_walls(int **map);


//player
int    move_player(t_player *player, int **map);
//void    rotate_player(t_player *player, float angle);
void    print_player(const t_player *player);

#endif