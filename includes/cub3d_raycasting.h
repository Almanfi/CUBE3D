/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycasting.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:39:12 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/18 23:26:57 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_RAYCASTING_H
#define CUB3D_RAYCASTING_H
#include "cub3d.h"
#include <X11/X.h>

# ifdef LINUX

#  define ESC_KEY 65307
#  define D_KEY 100
#  define A_KEY 97
#  define W_KEY 119
#  define S_KEY 115
#  define P_KEY 112
#  define C_KEY 99
#  define SLASH_KEY 47
#  define RIGHT_KEY 65363
#  define LEFT_KEY 65361
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define FORWARD_SCROLL 5
#  define BACKWARDS_SCROLL 4
#  define LEFT_CLIC 1
#  define RIGHT_CLIC 2

# else

#  define ESC_KEY 53
#  define D_KEY 2
#  define A_KEY 0
#  define W_KEY 13
#  define S_KEY 1
#  define P_KEY 35
#  define C_KEY 8
#  define SLASH_KEY 47
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define FORWARD_SCROLL 5
#  define BACKWARDS_SCROLL 4
#  define LEFT_CLIC 1
#  define RIGHT_CLIC 2

# endif // LINUX

// X11 Event Masks
# define NOEVENTMASK 0L
# define KEYPRESSMASK 1L
# define KEYRELEASEMASK 2L
# define BUTTONPRESSMASK 4L
# define BUTTONRELEASEMASK 8L
# define POINTERMOTIONMASK 64L

// X11 Event Names

# define KEYPRESS 2
# define KEYRELEASE 3
# define BUTTONPRESS 4
# define BUTTONRELEASE 5
# define MOTIONNOTIFY 6
# define DESTROYNOTIFY 17


// floor.c
void    cast_floor(t_cub3d *cub3d);

// hooks.c
void	cub3d_hooks(t_cub3d *cub3d);

// main_raycasting.c
void	draw_cub3d(t_cub3d *cub3d);
t_boolean	cast_rays_for_collision(t_cub3d *cub3d, double x, double y);

// walls.c
void    draw_wall(t_cub3d *cub3d, size_t x);

//movement.c
void	move_player(t_cub3d *cub3d);
void	rotate_player(t_cub3d *cub3d);
void    move_backwards(t_cub3d *cub3d);
void    move_forwards(t_cub3d *cub3d);
void    move_left(t_cub3d *cub3d);
void    move_right(t_cub3d *cub3d);
void    rotate_clockwise(t_cub3d *cub3d);
void    rotate_reverse_clockwise(t_cub3d *cub3d);

#endif