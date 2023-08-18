/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:59:39 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/17 17:11:32:48oulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int    close_window(void)
{
	ft_free(0, TRUE);
	exit(0);
	return (0);
}

void	print_map(t_cub3d *cub3d)
{
	int x;
	int y;

	printf("player at x = %lf, y = %lf\n", cub3d->raycaster.player_x, cub3d->raycaster.player_y);
	printf("camera at x = %lf, y = %lf\n", cub3d->raycaster.direction_x, cub3d->raycaster.direction_y);

	y = 0;
	while(cub3d->mini_map[y])
	{
		x = 0;
		while (cub3d->mini_map[y][x])
		{
			printf("%c, ", cub3d->mini_map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

static int	keyboard_press_hooks(int keycode,t_cub3d *cub3d)
{
	printf("dist to wall %lf\n", cub3d->raycaster.perpwallDist);
	if (keycode == ESC_KEY)
		close_window();
	else if (keycode == W_KEY)
		cub3d->move_vertical = 1;
	else if (keycode == S_KEY)
		cub3d->move_vertical = -1;
	else if (keycode == D_KEY)
		cub3d->move_horizontal = 1;
	else if (keycode == A_KEY)
		cub3d->move_horizontal = -1;
	else if (keycode == LEFT_KEY)
		cub3d->rotation_dir = -1;
	else if (keycode == RIGHT_KEY)
		cub3d->rotation_dir = 1; 
	else if (keycode == SLASH_KEY) //clean this
		print_map(cub3d);
	return (0);
}

static int	keyboard_release_hooks(int keycode,t_cub3d *cub3d)
{
	if (keycode == ESC_KEY)
		close_window();
	else if (keycode == S_KEY || keycode == W_KEY)
		cub3d->move_vertical = 0;
	else if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		cub3d->rotation_dir = 0;
	else if (keycode == A_KEY || keycode == D_KEY)
		cub3d->move_horizontal = 0;
	return (0);
}

void draw_texture(t_cub3d *cub3d)
{
	int	x;
	int	y;
	
	y = 0;
	printf("cub3d->img_height = %d\n", cub3d->img_height);
	while (y < cub3d->img_height * 5)
	{
		x = 0;
		while (x < cub3d->img_width * 5)
		{
			cub3d_pixel_put(cub3d, y, x, ((int *) cub3d->img)[x + (y * cub3d->img_height)]);
			x++;
		}
		y++;
	}
}

int	refresh(t_cub3d *cub3d)
{
	draw_cub3d(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->img, 0, 0);

		int x;
		int y;
		t_raycaster_data *raycaster;

		raycaster = &cub3d->raycaster;
		y = raycaster->player_x + cub3d->move_vertical * raycaster->direction_x * (MOVE_SPEED + HB_RADIUS)
			+ 0.7 * cub3d->move_horizontal * raycaster->camera_x * (MOVE_SPEED + HB_RADIUS);
		x = raycaster->player_y;
		if (cub3d->mini_map[x][y] == '0')
			raycaster->player_x += cub3d->move_vertical * raycaster->direction_x * MOVE_SPEED
				+ 0.7 * cub3d->move_horizontal * raycaster->camera_x * (MOVE_SPEED + HB_RADIUS);
		y = raycaster->player_x;
		x = raycaster->player_y + cub3d->move_vertical * raycaster->direction_y * (MOVE_SPEED + HB_RADIUS)
			+ 0.7 * cub3d->move_horizontal * raycaster->camera_y * (MOVE_SPEED + HB_RADIUS);
		if (cub3d->mini_map[x][y] == '0')
			raycaster->player_y += cub3d->move_vertical * raycaster->direction_y * MOVE_SPEED
			+ 0.7 * cub3d->move_horizontal * raycaster->camera_y * (MOVE_SPEED + HB_RADIUS);
		double	old_directionX;
		double	old_cameraX;
		double			rot_speed;

		rot_speed = cub3d->rotation_dir * degree_to_rad(ROT_SPEED);
		old_directionX = raycaster->direction_x;
		old_cameraX = raycaster->camera_x;
		raycaster->direction_x = old_directionX * cos(rot_speed) - raycaster->direction_y * sin(rot_speed);
		raycaster->direction_y = old_directionX * sin(rot_speed) + raycaster->direction_y * cos(rot_speed);
		raycaster->camera_x = old_cameraX * cos(rot_speed) - raycaster->camera_y * sin(rot_speed);
		raycaster->camera_y = old_cameraX * sin(rot_speed) + raycaster->camera_y * cos(rot_speed);
	return (0);
}

void	cub3d_hooks(t_cub3d *cub3d)
{
	// mlx_hook(cub3d->window, MOTIONNOTIFY, POINTERMOTIONMASK, rotate_hook,
	// 	fdf);
	mlx_hook(cub3d->window, DESTROYNOTIFY, NOEVENTMASK, close_window,(void *) NULL);
	mlx_hook(cub3d->window, KEYPRESS, KEYPRESSMASK, keyboard_press_hooks, cub3d);
	mlx_hook(cub3d->window, KEYRELEASE, KEYRELEASEMASK, keyboard_release_hooks, cub3d);
	mlx_loop_hook(cub3d->mlx, refresh, cub3d);
}
