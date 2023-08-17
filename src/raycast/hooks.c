/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:59:39 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/17 02:36:09 by maboulkh         ###   ########.fr       */
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

int	keyboard_hooks(int keycode,t_cub3d *cub3d)
{
	printf("dist to wall %lf\n", cub3d->raycaster.perpwallDist);
	if (keycode == ESC_KEY)
		close_window();
	else if (keycode == S_KEY)
		move_backwards(cub3d);
	else if (keycode == SLASH_KEY)
		print_map(cub3d);
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
