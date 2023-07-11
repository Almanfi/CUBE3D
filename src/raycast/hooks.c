/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:59:39 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/11 07:52:28 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int    close_window(void)
{
	ft_free(0, TRUE);
	exit(0);
	return (0);
}

int	keyboard_hooks(int keycode,t_cub3d *cub3d)
{
	if (keycode == ESC_KEY)
		close_window();
	else if (keycode == S_KEY)
		move_backwards(cub3d);
	else if (keycode == W_KEY)
		move_forwards(cub3d);
	else if (keycode == A_KEY)
		rotate_reverse_clockwise(cub3d);
	else if (keycode == D_KEY)
		rotate_clockwise(cub3d);
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
