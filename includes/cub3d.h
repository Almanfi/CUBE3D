/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:47:21 by maboulkh          #+#    #+#             */
/*   Updated: 2023/08/18 18:47:26 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "ft_garbage_collector.h"
#include <errno.h>
#include "mlx.h"
#include <math.h>

#define WINDOW_HEIGHT   1080
#define WINDOW_WIDTH    1920

#define TX_NBR   8
#define TEX_DIMENSIONS 64
#define HB_RADIUS 0.5

#define MOVE_SPEED 0.1
#define ROT_SPEED 5

#define CAMERA_DIR_X 1.0
#define CAMERA_DIR_Y 0.0
#define CAMERA_FOV_X 0.0
#define CAMERA_FOV_Y 0.66

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}   t_rgb;


typedef struct s_frame_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_frame_data;

typedef enum e_tx_type
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    FLOOR,
    NOT_DEFINED
}   t_tx_type;

typedef struct s_textures
{
    // t_boolean   north;
    // t_boolean   east;
    // t_boolean   south;
    // t_boolean   west;
    t_rgb       floor;
    t_boolean   floor_is_set;
    void        *tx_img[TX_NBR];
    int         tx[TX_NBR][TEX_DIMENSIONS * TEX_DIMENSIONS];
    int         tx_set[TX_NBR];
}   t_textures;

typedef struct  s_player_move
{
    double x;
    double y;
}   t_player_move;

#define X 0
#define Y 1

typedef struct  s_raycaster_data
{
    size_t  rows_count;
    // player pos;
    double	player_x;
	double	player_y;
    // camera plane and direction
	double	direction_x;
	double	direction_y;
	double	camera_x;
	double	camera_y;
    // ray casting wall data;
    double  rayX;
    double  rayY;
    int     mapX;
    int     mapY;
    double  sideDistX;
    double  sideDistY;
    double  deltadistX;
    double  deltadistY;
    double  perpwallDist;
    int     step_x;
    int     step_y;
    t_boolean     hit;
    t_boolean     side;
    // drawing wall data
    int           draw_start;
    int           draw_end;
    double	wallX;
	double	tex_step;
	double	tex_pos;
	int		texX;
	int		texY;
    // raycasting floor data
    double  leftest_ray[2];
    double  rightest_ray[2];
    int     current_y;
    double  vertical_pos;
    double  row_distance;
    double  floor_step[2];
    double  floor_cords[2];
}   t_raycaster_data;

typedef struct s_cub3d
{
    char        **map_content;
    size_t      *content_len;         
    char        **mini_map;
    size_t      *mini_map_line_len;
    t_boolean   player_set;
    t_textures  texture;
    void        *mlx;
    void        *window;
    void        *img;
    int		img_width;
	int		img_height;
    t_frame_data    frame;
    t_player_move   p_move;
    t_raycaster_data    raycaster;
}   t_cub3d;

// mlx
// init_mlx.c
void    cub3d_window_init(t_cub3d *cub3d);
void    cub3d_frame_init(t_cub3d *cub3d);
void    cub3d_mlx_init(t_cub3d *cub3d);
//  pixel_put.c
void    cub3d_pixel_put(t_cub3d *cub3d, int x, int y, unsigned int color);

// exit_cub3d.c
void    exit_cub3d(int  err_code, char *message);

// utils
//math_utils.c
double ft_abs(double value);
double  degree_to_rad(double degree);

// map_utils.c
void    skip_empty_lines(t_cub3d *cub3d);
void    justify_lines(t_cub3d *cub3d);

//skip_space.c
t_boolean	ft_is_space(char c);
char        *skip_space(char *str);
// strdup.c
char	*pro_strdup(char *str);
//substr.c
char	*pro_substr(char const *s, unsigned int start, size_t len);
// array_utils.c
void	*add_element_to_array(void *old_array, void *new_elem, size_t data_size);
void	*add_arr_to_array(void *dest_arr, void *src_arr, size_t data_size);

#include "cub3d_parsing.h"
#include "cub3d_raycasting.h"

#endif