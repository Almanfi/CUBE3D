/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:59:39 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/11 04:32:31 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MOVE_SPEED 0.3
#define ROT_SPEED 10

int    close_window(void)
{
	ft_free(0, TRUE);
	exit(0);
	return (0);
}

int	keyboard_hooks(int keycode,t_cub3d *cub3d)
{
	int	x, y;
	t_raycaster_data *raycaster;
	double			rot_speed;
	
	rot_speed = degree_to_rad(ROT_SPEED);
	raycaster = &cub3d->raycaster;
	if (keycode == ESC_KEY)
		close_window();
	else if (keycode == S_KEY)
	{
		x = raycaster->player_x - raycaster->direction_x * MOVE_SPEED;
		y = raycaster->player_y;
		if (cub3d->mini_map[x][y] == '0')
			raycaster->player_x -= raycaster->direction_x * MOVE_SPEED;
		x = raycaster->player_x;
		y = raycaster->player_y - raycaster->direction_y * MOVE_SPEED;
		if (cub3d->mini_map[x][y] == '0')
			raycaster->player_y -= raycaster->direction_y * MOVE_SPEED;
	}
	else if (keycode == W_KEY)
	{
		x = raycaster->player_x + raycaster->direction_x * MOVE_SPEED;
		y = raycaster->player_y;
		if (cub3d->mini_map[x][y] == '0')
			raycaster->player_x += raycaster->direction_x * MOVE_SPEED;
		x = raycaster->player_x;
		y = raycaster->player_y + raycaster->direction_y * MOVE_SPEED;
		if (cub3d->mini_map[x][y] == '0')
			raycaster->player_y += raycaster->direction_y * MOVE_SPEED;
	}
	else if (keycode == A_KEY)
	{
		double	old_directionX = raycaster->direction_x;
		raycaster->direction_x = old_directionX * cos(-rot_speed) - raycaster->direction_y * sin(-rot_speed);
		raycaster->direction_y = old_directionX * sin(-rot_speed) + raycaster->direction_y * cos(-rot_speed);
		double	old_cameraX = raycaster->camera_x;
		raycaster->camera_x = old_cameraX * cos(-rot_speed) - raycaster->camera_y * sin(-rot_speed);
		raycaster->camera_y = old_cameraX * sin(-rot_speed) + raycaster->camera_y * cos(-rot_speed);
	}
	else if (keycode == D_KEY)
	{
		double	old_directionX = raycaster->direction_x;
		raycaster->direction_x = old_directionX * cos(rot_speed) - raycaster->direction_y * sin(rot_speed);
		raycaster->direction_y = old_directionX * sin(rot_speed) + raycaster->direction_y * cos(rot_speed);
		double	old_cameraX = raycaster->camera_x;
		raycaster->camera_x = old_cameraX * cos(rot_speed) - raycaster->camera_y * sin(rot_speed);
		raycaster->camera_y = old_cameraX * sin(rot_speed) + raycaster->camera_y * cos(rot_speed);
	}
	return (0);
}

int	refresh(t_cub3d *cub3d)
{
	draw_cub3d(cub3d);
	return (0);
}

void	cub3d_hooks(t_cub3d *cub3d)
{
	mlx_hook(cub3d->window, DESTROYNOTIFY, NOEVENTMASK, close_window,(void *) NULL);
	mlx_hook(cub3d->window, KEYPRESS, KEYPRESSMASK, keyboard_hooks, cub3d);
	mlx_loop_hook(cub3d->mlx, refresh, cub3d);
}
