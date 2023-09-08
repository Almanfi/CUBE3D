/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:16:26 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/08 17:39:35 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_garbage_collector.h"
# include "mlx.h"
# include <errno.h>
# include <float.h>
# include <math.h>

# define WINDOW_HEIGHT 1080
# define WINDOW_WIDTH 1920

# define TX_NBR 16
# define TEX_DIMENSIONS 256
# define HB_RADIUS 0.3

# define MOVE_SPEED 0.4
# define ROT_SPEED 4

typedef struct s_cub3d_projected_point
{
	double				x;
	double				y;
	int					clr;
}						t_projected_point;

typedef struct s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

typedef struct s_frame_data
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_frame_data;

typedef enum e_tx_type
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	DOOR,
	SPRITE,
	FIREHEAD1,
	FIREHEAD2,
	FIREHEAD3,
	FIREHEAD4,
	FIREHEAD5,
	NOT_DEFINED
}						t_tx_type;

typedef struct s_textures
{
	t_rgb				floor;
	t_boolean			floor_is_set;
	t_rgb				ceiling;
	t_boolean			ceiling_is_set;
	void				*tx_img[TX_NBR];
	int					tx[TX_NBR][TEX_DIMENSIONS * TEX_DIMENSIONS];
	int					tx_set[TX_NBR];
}						t_textures;

typedef struct s_player_move
{
	double				x;
	double				y;
}						t_player_move;

typedef struct s_raycaster_data
{
	size_t				rows_count;
	double				player_x;
	double				player_y;
	double				direction_x;
	double				direction_y;
	double				camera_x;
	double				camera_y;
	double				rayX;
	double				rayY;
	int					mapX;
	int					mapY;
	double				sideDistX;
	double				sideDistY;
	double				deltadistX;
	double				deltadistY;
	double				perpwallDist;
	int					step_x;
	int					step_y;
	t_boolean			hit;
	t_boolean			side;
	t_boolean			door;
	t_boolean			door_side;
	int					backX;
	int					backY;
	t_boolean			backS;
	t_boolean			pass_door;
	double				angle;
	double				delta;
	int					draw_start;
	int					draw_end;
	double				wallX;
	double				tex_step;
	double				tex_pos;
	int					texX;
	int					texY;
	double				sprite_x;
	double				sprite_y;
	double				inv_Det;
	double				transform_X;
	double				transform_Y;
	int					sprite_screenX;
	int					sprite_height;
	int					draw_startX;
	int					draw_startY;
	int					draw_endX;
	int					draw_endY;
	int					sprite_width;

}						t_raycaster_data;

typedef struct s_sprite
{
	double				x;
	double				y;
	size_t				sprite_id;
	double				distance;
}						t_sprite;

typedef struct s_minimap
{
	int					width;
	int					height;
	int					unit;
	int					size;
}						t_minimap;

typedef struct s_door
{
	int					x;
	int					y;
	float				open;
	t_boolean			opening;
}						t_door;

typedef struct s_cub3d
{
	char				**map_content;
	size_t				*content_len;
	size_t				map_len;
	size_t				*map_row_len;
	char				**mini_map;
	size_t				*mini_map_line_len;
	t_boolean			player_set;
	t_textures			texture;
	void				*mlx;
	void				*window;
	void				**imgs;
	int					img_width;
	int					img_height;
	t_frame_data		frame;
	t_player_move		p_move;
	t_raycaster_data	raycaster;
	int					move_horizontal;
	int					move_vertical;
	int					rotation_dir;
	t_sprite			**sprites;
	size_t				sprite_count;
	double				Zbuffer[WINDOW_WIDTH];
	int					mouse_x;
	int					mouse_y;
	double				rot_multiplicator;
	int					texturen;
	t_minimap			minimap;
	t_door				**door;
}						t_cub3d;

//  main.c
t_cub3d					*get_cub3d(t_cub3d *cub3d);
// mlx
// init_mlx.c
void					cub3d_window_init(t_cub3d *cub3d);
void					cub3d_frame_init(t_cub3d *cub3d);
void					cub3d_mlx_init(t_cub3d *cub3d);
//  pixel_put.c
void					cub3d_pixel_put(t_cub3d *cub3d, int x, int y,
							unsigned int color);
//  draw_line.c
void					cub3d_draw_line(t_cub3d *cub3d,
							t_projected_point point1, t_projected_point point2);
void					get_new_points(t_cub3d *cub3d, t_projected_point *p1,
							t_projected_point *p2);
void					pointer_swap(void **a, void **b);
void					double_swap(double *a, double *b);

// exit_cub3d.c
void					exit_cub3d(int err_code, char *message);

// utils
// camera_start.c
void					set_camera_cord(t_cub3d *cub3d, char c);
// math_utils.c
double					ft_abs(double value);
double					degree_to_rad(double degree);
// set_map.c
void					set_mini_map(t_cub3d *cub3d, size_t last_line);
// map_utils.c
void					skip_empty_lines(t_cub3d *cub3d);
void					justify_lines(t_cub3d *cub3d);
t_boolean				is_open_door(t_door **door, int x, int y,
							float *door_open_ratio);
t_boolean				open_wall(char **map, size_t i,
							size_t j);

// skip_space.c
t_boolean				ft_is_space(char c);
char					*skip_space(char *str);
size_t					clamp_trailing_space(char *line);
// strdup.c
char					*pro_strdup(char *str);
// substr.c
char					*pro_substr(char const *s, unsigned int start,
							size_t len);
// array_utils.c
void					*add_element_to_array(void *old_array, void *new_elem,
							size_t data_size);
void					*add_arr_to_array(void *dest_arr, void *src_arr,
							size_t data_size);
void					*rm_element_from_array(void *old_array, void *elem,
							size_t data_size);

# include "cub3d_parsing.h"
# include "cub3d_raycasting.h"

#endif