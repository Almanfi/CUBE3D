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
	t_cub3d *cub3d;

	cub3d = get_cub3d(NULL);
	while (*(cub3d->imgs))
	{
		mlx_destroy_image(cub3d->mlx, *(cub3d->imgs));
		cub3d->imgs++;
	}
	mlx_destroy_window(cub3d->mlx, cub3d->window);
	ft_free(0, TRUE);
	exit(0);
	return (0);
}

void	print_map(t_cub3d *cub3d)
{
	// int x;
	// int y;

	printf("player at x = %lf, y = %lf\n", cub3d->raycaster.player_x, cub3d->raycaster.player_y);
	// printf("direction at  at x = %lf, y = %lf\n", cub3d->raycaster.direction_x, cub3d->raycaster.direction_y);
	// printf("FOV at x = %lf , y = %lf\n", cub3d->raycaster.camera_x, cub3d->raycaster.camera_y);
	// y = 0;
	// while(cub3d->mini_map[y])
	// {
	// 	x = 0;
	// 	while (cub3d->mini_map[y][x])
	// 	{
	// 		printf("%c, ", cub3d->mini_map[y][x]);
	// 		x++;
	// 	}
	// 	printf("\n");
	// 	y++;
	// }
}

static int	keyboard_press_hooks(int keycode,t_cub3d *cub3d)
{
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
	else if (keycode == C_KEY) //clean this
		open_door(cub3d, cub3d->door);
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

int	refresh(t_cub3d *cub3d)
{
	static int fps;
	
	if (fps > 500)
	{
		animate_doors(cub3d, cub3d->door);
		if (cub3d->move_vertical || cub3d->move_horizontal)
			move_player(cub3d);
		if (cub3d->rotation_dir)
			rotate_player(cub3d);
		draw_cub3d(cub3d);
		draw_minimap(cub3d);
		fps = 0;
		cub3d->texturen++;
		if (cub3d->texturen > 4)
			cub3d->texturen = 0;
	}
	fps++;
	return (0);
}

// int	mouse_rotation(int x, int y, t_cub3d *cub3d)
// {
// 	if (x - cub3d->mouse_x > 0)
// 	{
		
// 		cub3d->rotation_dir = 1;
// 	}
// 	return (0);
// }	

void	cub3d_hooks(t_cub3d *cub3d)
{
	cub3d->mouse_x = WINDOW_HEIGHT / 2;
	cub3d->mouse_y = WINDOW_WIDTH / 2;
	// mlx_hook(cub3d->window, MOTIONNOTIFY, POINTERMOTIONMASK, rotate_hook,
	// 	fdf);
	mlx_hook(cub3d->window, DESTROYNOTIFY, NOEVENTMASK, close_window,(void *) NULL);
	mlx_hook(cub3d->window, KEYPRESS, KEYPRESSMASK, keyboard_press_hooks, cub3d);
	mlx_hook(cub3d->window, KEYRELEASE, KEYRELEASEMASK, keyboard_release_hooks, cub3d);
	mlx_loop_hook(cub3d->mlx, refresh, cub3d);
}
