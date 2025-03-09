#ifndef CUB3D_H
# define CUB3D_H

#define ROWS 7
#define COLS 7
#define WALL_SIZE 6400
#define STEP_SIZE 1000
#define	FOV_ANGLE 90
#define	FOV_WIDTH 1600
#define FOV_HEIGHT 900
#define RED_COLOR "\033[31m"
#define RESET_COLOR "\033[0m"
#define SKY_COLOR 0x87CEEB
#define FLOOR_COLOR 0x013220

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "./mlx/mlx.h"

typedef struct s_fov
{
	float	dist;
	int		wall_texture;
	float	pos_hit;
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
	float		virtual_x;
	float		virtual_y;
	//player's direction
	int		dir;
	//Field of view (FOV)
	struct s_fov	plane[FOV_WIDTH];
	//last ray hit (enum t_walltexture)
	int		last_hit;
	float		pos_hit;
	
} t_player;

typedef struct s_game {
    void 				*mlx;
    void 				*win;
	int					**map;
    t_player			player;
	struct s_texture	*textures[4];
	t_img				img;
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

typedef struct s_wall_data
{
    int		tex_x;
    float	tex_step;
    int		start_y;
    int		end_y;
	int		line_height;
} t_wall_data;

typedef struct s_xypos
{
	int		temp_xy[2];
	float	temp_v_xy[2];
} t_xypos;


//map_utils
//void	print_map(int **map, int rows, int cols);
//void	expand_map(int **new_map, int **map);
void	free_map(int **map, int rows);
int		**alloc_map(int rows, int cols);
int		get_ylen(int **map);
int		get_xlen(int **map);

//Calculate ray's dist
float	ft_get_ray_dist(double angle, t_player *player, int **map);
t_fov	ft_get_ray(double angle, t_player *player, int **map);

//Math
float	calc_q_one(double angle, t_player *player, int **map, t_xypos *pos);
float	calc_q_two(double angle, t_player *player, int **map, t_xypos *pos);
float	calc_q_three(double angle, t_player *player, int **map, t_xypos *pos);
float	calc_q_four(double angle, t_player *player, int **map, t_xypos *pos);
float	calc_notables(double angle, t_player *player, int **map, t_xypos *pos);

//Construct FOV
void	ft_build_fov(t_player *player, int **map);

//Textures
t_texture   *load_texture(void *mlx, char *path);
t_texture *get_texture(t_game *game, int texture_id);

//Image
int get_pixel_color(t_texture *tex, int x, int y);
void draw_window(t_game *game, t_player *player);
void	put_pixel(t_game *game, int x, int y, int color);
int	get_pixel_color(t_texture *tex, int x, int y);
int	get_line_height(int x, t_player *player);
void	draw_wall_column(t_game *game, t_texture *texture,
	int x, t_wall_data *wall);
void	setup_wall_data(t_wall_data *wall,
	t_texture *texture, float pos_hit, int line_height);


//Key hook
int key_hook(int keycode, t_game *game);


//player
//int    move_player(t_player *player, int **map);
//void    rotate_player(t_player *player, float angle);
//void    print_player(const t_player *player);

#endif