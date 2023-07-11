/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:37:34 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/11 05:41:46 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

#include "ft_garbage_collector.h"
#include <errno.h>
#include <mlx.h>
#include <math.h>

#define WINDOW_HEIGHT   1080
#define WINDOW_WIDTH    1920

#define TEX_DIMENSIONS 64

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}   t_rgb;


typedef struct s_textures
{
    int         north;
    int         east;
    int         south;
    int         west;
    t_rgb       floor;
    t_boolean   floor_is_set;
    int         r_textures[8][TEX_DIMENSIONS * TEX_DIMENSIONS];
}   t_textures;

typedef struct s_frame_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_frame_data;

typedef struct  s_player_move
{
    double x;
    double y;
}   t_player_move;

typedef struct  s_raycaster_data
{
    size_t  rows_count;
    size_t  columns_count;
    double	player_x;
	double	player_y;
	double	direction_x;
	double	direction_y;
	double	camera_x;
	double	camera_y;
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
    int           draw_start;
    int           draw_end;
    double	wallX;
	double	tex_step;
	double	tex_pos;
	int		texX;
	int		texY;
}   t_raycaster_data;

typedef struct s_cub3d
{
    char        **map_content;
    size_t      *content_len;         
    char        **mini_map;
    t_boolean   player_set;
    t_textures  texture;
    void        *mlx;
    void        *window;
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