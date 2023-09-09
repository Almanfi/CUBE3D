/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:57:45 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/08 22:58:20 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(void)
{
	t_cub3d	*cub3d;

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

static int	keyboard_press_hooks(int keycode, t_cub3d *cub3d)
{
	if (keycode == ESC_KEY)
		close_window();
	if (keycode == W_KEY)
		cub3d->move_vertical = 1;
	if (keycode == S_KEY)
		cub3d->move_vertical = -1;
	if (keycode == D_KEY)
		cub3d->move_horizontal = 1;
	if (keycode == A_KEY)
		cub3d->move_horizontal = -1;
	if (keycode == LEFT_KEY)
		cub3d->rotation_dir = -1;
	if (keycode == RIGHT_KEY)
		cub3d->rotation_dir = 1;
	if (keycode == C_KEY)
		open_door(cub3d, cub3d->door);
	return (0);
}

static int	keyboard_release_hooks(int keycode, t_cub3d *cub3d)
{
	if (keycode == ESC_KEY)
		close_window();
	if (keycode == S_KEY || keycode == W_KEY)
		cub3d->move_vertical = 0;
	if (keycode == A_KEY || keycode == D_KEY)
		cub3d->move_horizontal = 0;
	return (0);
}

int	refresh(t_cub3d *cub3d)
{
	static int	fps;

	if (fps > 1000)
	{
		animate_doors(cub3d, cub3d->door);
		// if (cub3d->move_vertical || cub3d->move_horizontal)
			move_player(cub3d);
		// if (cub3d->rotation_dir)
			rotate_player(cub3d);
		cub3d->rotation_dir = 0;
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

void	cub3d_hooks(t_cub3d *cub3d)
{
	cub3d->mouse_x = WINDOW_HEIGHT / 2;
	cub3d->mouse_y = WINDOW_WIDTH / 2;
	cub3d->minimap.size = 5;
	cub3d->minimap.unit = 10;
	cub3d->minimap.height = WINDOW_HEIGHT / cub3d->minimap.size;
	cub3d->minimap.width = WINDOW_WIDTH / cub3d->minimap.size;
	mlx_hook(cub3d->window, MOTIONNOTIFY, POINTERMOTIONMASK, mouse_rotation,
		cub3d);
	mlx_hook(cub3d->window, DESTROYNOTIFY, NOEVENTMASK, close_window,
		(void *) NULL);
	mlx_hook(cub3d->window, KEYPRESS, KEYPRESSMASK, keyboard_press_hooks,
		cub3d);
	mlx_hook(cub3d->window, KEYRELEASE, KEYRELEASEMASK, keyboard_release_hooks,
		cub3d);
	mlx_loop_hook(cub3d->mlx, refresh, cub3d);
}
