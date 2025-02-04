#ifndef CUB3D_H
# define CUB3D_H

#define ROWS 7
#define COLS 7
#define WALL_SIZE 64
#define STEP_SIZE 10
#define	FOV_ANGLE 100
#define	FOV_WIDTH 1024
#define FOV_HEIGHT 512
#define RED_COLOR "\033[31m"
#define RESET_COLOR "\033[0m"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_fov
{
	float	dist;
	int	wall_texture;
	int	pos_hit;
} t_fov;

typedef struct s_img
{
    void    *ptr;  // Pointer to the MLX image
    char    *addr; // Address of image data
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img;


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
	int		pos_hit;
	
} t_player;

typedef struct s_game {
    void *mlx;
    void *win;
	int	**map;
    t_player player;
	struct s_texture *textures[4];
	t_img	img;
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

typedef struct s_texture {
    void    *img;       // Ponteiro para a imagem carregada pelo mlx
    int     *data;      // Pixels da imagem
    int     width;      // Largura da textura
    int     height;     // Altura da textura
    int     bpp;        // Bits por pixel
    int     size_line;  // Tamanho da linha em bytes
    int     endian;     // Endianess da imagem
} t_texture;

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