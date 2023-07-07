/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:37:34 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/07 21:47:46 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

#include "ft_garbage_collector.h"
#include "errno.h"
#include <mlx.h>
#include <math.h>

#define WINDOW_HEIGHT   1080
#define WINDOW_WIDTH    1920
#define DATA_SCOPE      17

typedef enum e_side
{
    UP,
    DOWN,
    LEFT,
    RIGHT
}   t_side;

typedef struct s_point
{
    int     x;
    int     y;
    t_side  side;
}   t_point;

typedef struct s_point2
{
    float     x;
    float     y;
}   t_pnt2;

typedef struct s_wall
{
    t_side  side;
    int     s;
    int     from;
    int     to;
    float   a;
    float   b;
    float   c;
}   t_wall;

typedef struct s_walls
{
    t_wall  **up;
    t_wall  **down;
    t_wall  **left;
    t_wall  **right;
}   t_walls;



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
}   t_textures;

typedef struct s_frame_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_frame_data;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	v_angle;
    float   a1;
    float   a2;
}	t_player;

typedef struct s_cub3d
{
	char			**map_content;
	char			**mini_map;
	t_boolean		player_set;
	t_textures		texture;
	void			*mlx;
	void			*window;
	t_frame_data	frame;
	t_walls			walls;
	t_player		player;
}   t_cub3d;

// mlx
// init_mlx.c
void    cub3d_window_init(t_cub3d *cub3d);
void    cub3d_frame_init(t_cub3d *cub3d);
void    cub3d_mlx_init(t_cub3d *cub3d);

// exit_cub3d.c
void    exit_cub3d(int  err_code, char *message);

// utils
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