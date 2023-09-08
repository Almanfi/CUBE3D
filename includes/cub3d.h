/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:16:26 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/08 20:41:00 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_def.h"
# include "cub3d_parsing.h"
# include "cub3d_raycasting.h"

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

#endif
