#ifndef CUB3D_H
# define CUB3D_H

#define ROWS 5
#define COLS 5
#define WALL_SIZE 64
#define STEP_SIZE 5
#define	FOV_ANGLE 120
#define	FOV_WIDTH 320
#define FOV_HEIGHT 640
#define RED_COLOR "\033[31m"
#define RESET_COLOR "\033[0m"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_fov
{
	int	dist;
	int	wall_texture;
} t_fov;

typedef struct s_player
{
	//player's position in original grid
	int		pos_x;
	int		pos_y;
	//player's virtual position
	int		virtual_x;
	int		virtual_y;
	//player's direction
	int		dir;
	//Field of view (FOV)
	struct s_fov	plane[FOV_ANGLE];
	//last ray hit (enum t_walltexture)
	int		last_hit;
	
} t_player;

typedef struct s_game {
    void *mlx;
    void *win;
	int	**map;
    t_player player;
} t_game;

typedef enum e_walltexture
{
	FLOOR,
	WALL,
	N_DIR,
	S_DIR,
	W_DIR,
	E_DIR
} t_walltexture;


//map_utils
void print_map(int **map, int rows, int cols);
void expand_map(int **new_map, int **map);
void free_map(int **map, int rows);
int **alloc_map(int rows, int cols);
int get_ylen(int **map);
int get_xlen(int **map);
//void    enum_walls(int **map);


//player
int    move_player(t_player *player, int **map);
//void    rotate_player(t_player *player, float angle);
void    print_player(const t_player *player);

#endif