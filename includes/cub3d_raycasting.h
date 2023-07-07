/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycasting.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:39:12 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/07 18:31:56 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_RAYCASTING_H
#define CUB3D_RAYCASTING_H
#include "cub3d.h"

#define CUBE_DIMENSIONS 64


# define ESC_KEY 53
# define D_KEY 2
# define A_KEY 0
# define W_KEY 13
# define S_KEY 1
# define P_KEY 35
# define C_KEY 8
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define UP_KEY 126
# define DOWN_KEY 125
# define FORWARD_SCROLL 5
# define BACKWARDS_SCROLL 4
# define LEFT_CLIC 1
# define RIGHT_CLIC 2

// X11 Event Masks
# define NOEVENTMASK 0L
# define KEYPRESSMASK 1L
# define BUTTONPRESSMASK 4L
# define BUTTONRELEASEMASK 8L
# define POINTERMOTIONMASK 64L

// X11 Event Names

# define KEYPRESS 2
# define BUTTONPRESS 4
# define BUTTONRELEASE 5
# define MOTIONNOTIFY 6
# define DESTROYNOTIFY 17

// hooks.c
void	cub3d_hooks(t_cub3d *cub3d);

// main_raycasting.c
void	draw_cub3d(t_cub3d *cub3d);

#endif