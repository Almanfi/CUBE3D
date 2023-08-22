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
	int x;
	int y;

	printf("player at x = %lf, y = %lf\n", cub3d->raycaster.player_x, cub3d->raycaster.player_y);
	printf("direction at  at x = %lf, y = %lf\n", cub3d->raycaster.direction_x, cub3d->raycaster.direction_y);
	printf("FOV at x = %lf , y = %lf\n", cub3d->raycaster.camera_x, cub3d->raycaster.camera_y);
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

static t_boolean	check_map(int x, int y, t_cub3d *cub3d, int minimap_size)
{
	int	xm;
	int	ym;
	int ratio;

	ratio = 10;
	xm = x - WINDOW_WIDTH / minimap_size  + (cub3d->raycaster.player_x * ratio);
	ym = y - WINDOW_HEIGHT / minimap_size + (cub3d->raycaster.player_y * ratio);
	if (ym >= 0 && ym / ratio < (int) cub3d->raycaster.rows_count
		&& xm >= 0 && xm / ratio < (int) cub3d->mini_map_line_len[ym / ratio]
		&& cub3d->mini_map[ym / ratio][xm / ratio] == '0'
		)
		return (TRUE);
	else
		return (FALSE);
}

void	draw_minimap(t_cub3d *cub3d)
{
	int	x;
	int	y;
	int ratio;
	int minimap_size;

	minimap_size = 20;
	ratio = 10;
	y =  0;
	while (y <  2 * WINDOW_HEIGHT / minimap_size)
	{
		x =  0;
		while (x < 2 * WINDOW_WIDTH / minimap_size)
		{
			if (y > WINDOW_HEIGHT / minimap_size - ratio / 2 && y < WINDOW_HEIGHT / minimap_size + ratio / 2
				&& x > WINDOW_WIDTH / minimap_size - ratio / 2 && x < WINDOW_WIDTH / minimap_size + ratio / 2)
				cub3d_pixel_put(cub3d, x, y, 0xff0000);
			else if (check_map(x, y, cub3d, minimap_size))
				cub3d_pixel_put(cub3d, x, y, 0xffffff);
			else
				cub3d_pixel_put(cub3d, x, y, 0x000000);
			x++;
		}
		y++;
	}
	t_projected_point start;
	t_projected_point end;
	t_raycaster_data *raycaster;

	int length = 500;
    raycaster = &cub3d->raycaster;
	start.x = WINDOW_WIDTH / minimap_size;
	start.y = WINDOW_HEIGHT / minimap_size;
	end.x = start.x + length * (raycaster->direction_x * (MOVE_SPEED + HB_RADIUS)
        + raycaster->camera_x * (MOVE_SPEED + HB_RADIUS));
    end.y = start.y + length * (raycaster->direction_y * (MOVE_SPEED + HB_RADIUS)
        + raycaster->camera_y * (MOVE_SPEED + HB_RADIUS));
	cub3d_draw_line(cub3d, start, end);
	end.x = start.x + length * (raycaster->direction_x * (MOVE_SPEED + HB_RADIUS)
        - raycaster->camera_x * (MOVE_SPEED + HB_RADIUS));
    end.y = start.y + length * (raycaster->direction_y * (MOVE_SPEED + HB_RADIUS)
        - raycaster->camera_y * (MOVE_SPEED + HB_RADIUS));
	cub3d_draw_line(cub3d, start, end);
}

int	refresh(t_cub3d *cub3d)
{
	static int fps;

	if (fps > 10000)
	{
		move_player(cub3d);
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
