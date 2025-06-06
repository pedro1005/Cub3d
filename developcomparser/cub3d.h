#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5 
# endif

#define WALL_SIZE 64
#define STEP_SIZE WALL_SIZE / 50
#define	FOV_ANGLE 60
#define	FOV_WIDTH 800
#define FOV_HEIGHT 600

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "./mlx/mlx.h"
#include <X11/Xlib.h>
#include <stdbool.h>

typedef struct s_fov
{
	float	dist;
	int		wall_texture;
	float	pos_hit;
} t_fov;

typedef struct s_win
{
	int	height;
	int	width;
	int	**map;
} t_win;

typedef struct s_img
{
    void    *ptr;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	float		virtual_x;
	float		virtual_y;
	int		dir;
	struct s_fov	plane[FOV_WIDTH];
	int		last_hit;
	float		pos_hit;
	
} t_player;

typedef struct s_tex_flags
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int	c;
	int	c_hexa;
	int	f;
	int	f_hexa;
	int nbr_of_tex_set;
	int	nbr_of_coulors_set;
}		t_tex_flags;

typedef struct s_game {
    void 				*mlx;
    void 				*win;
	int					**map;
	char				**mapchar;
	size_t					map_rows;
	size_t					map_cols;
	char				*map_str;
	t_tex_flags			*tex_values;
    t_player			*player;
	struct s_texture	*textures[4];
	t_img				img;
	int					keys[7];
	int					fd;
	char				*tex_path_in;
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

typedef enum e_keys
{
	KEY_FW,
	KEY_BCK,
	KEY_L,
	KEY_R,
	KEY_ROTATE_L,
	KEY_ROTATE_R,
	KEY_ESC
} t_keys;

typedef struct s_texture {
    void    *img;
    int     *data;
    int     width;
    int     height;
    int     bpp;
    int     size_line;
    int     endian;
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
void	free_map(int **map, int rows);
int		**alloc_map(t_game *game);
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
int close_window(t_game *game);

//libft
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
int	ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
bool	empty_line(char *line);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_isalpha(int c);
bool	ft_isspace(char c);
int	ft_isdigit(int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);

//Key hook
int key_hook(t_game *game);
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
void    get_map_size(char *file_name, t_game *game);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
void	map_insertion(int *matrix_row, char *line);
void    populate_map(char *str, t_game *g);

//player
void    move_right(t_player *player, int **map);
void    move_left(t_player *player, int **map);
void    move_backward(t_player *player, int **map);
void    move_forward(t_player *player, int **map);
float	*set_virt_xy(t_player *player, double rad);
double	get_rad(int dir, int key);
int	check_x_collision(float virt_x, int **map, t_player *player);

//parser
int	check_filename(char *file);
int	parser(char *input, t_game *g);
void    coulor_parser(t_game *g, char fc_coulor);
void    tex_parser(t_game *g, char wall);
void	get_map(t_game *g, char *line);
void	missing_text_color(t_game *g);
bool	tex_and_coulors_ready(t_game *g);
void	map_validator(t_game *g);

void	ft_exit(t_game *g, char *msg, int exitnbr);
void	ft_error_exit(t_game *g, char *msg);
void	free_pntr(void *mem);

#endif
