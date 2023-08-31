/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:46:29 by maboulkh          #+#    #+#             */
/*   Updated: 2023/08/31 01:00:51 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"

static void	set_ray_step(t_cub3d *cub3d)
{
	t_raycaster_data *raycaster;

	raycaster = &cub3d->raycaster;
	if (raycaster->rayX < 0)
	{
		raycaster->step_x = -1;
		raycaster->sideDistX = (raycaster->player_x - raycaster->mapX) * raycaster->deltadistX;
	}
	else
	{
		raycaster->step_x = 1;
		raycaster->sideDistX = (raycaster->mapX + 1.0 - raycaster->player_x) * raycaster->deltadistX;
	}
	if (raycaster->rayY < 0)
	{
		raycaster->step_y = -1;
		raycaster->sideDistY = (raycaster->player_y - raycaster->mapY) * raycaster->deltadistY;
	}
	else
	{
		raycaster->step_y = 1;
		raycaster->sideDistY = (raycaster->mapY + 1.0 - raycaster->player_y) * raycaster->deltadistY;
	}
}

static	void	perform_dda(t_cub3d *cub3d)
{
	t_raycaster_data *raycaster;
	int	backX;
	int	backY;
	t_boolean	backS;
	t_boolean	help;;
	double vec;
	double angle;
	double delta;

	raycaster = &cub3d->raycaster;
	backX = raycaster->mapX / 2;
	backY = raycaster->mapY / 2;
	backS = raycaster->side;
	help = FALSE;
	angle = atan(raycaster->rayY / raycaster->rayX);
	while (!raycaster->hit)
	{
		raycaster->door = FALSE;
		if (cub3d->mini_map[raycaster->mapY / 2][raycaster->mapX / 2] == 'D')
			raycaster->door = TRUE;
		if (raycaster->sideDistX < raycaster->sideDistY)
		{
			raycaster->sideDistX += raycaster->deltadistX;
			raycaster->mapX += raycaster->step_x;
			raycaster->side = FALSE;
		}
		else
		{
			raycaster->sideDistY += raycaster->deltadistY;
			raycaster->mapY += raycaster->step_y;
			raycaster->side = TRUE;
		}
		if ((raycaster->mapX <= 0 || raycaster->mapY <= 0
			|| raycaster->mapY / 2 > (int) cub3d->raycaster.rows_count
			|| raycaster->mapX / 2 > (int) cub3d->mini_map_line_len[raycaster->mapY / 2]
			|| cub3d->mini_map[raycaster->mapY / 2][raycaster->mapX / 2] == 'D'))
		{
			if (cub3d->mini_map[backY][backX] == 'D' && (backS == raycaster->side || help))
			{
				vec = 1;
				if (raycaster->side) // by x
				{
					if (raycaster->rayY > 0)
						delta = (double) (raycaster->mapY - raycaster->player_y);
					else
						delta = (double) (raycaster->mapY - raycaster->player_y + 1);
					vec = (raycaster->player_x + (delta) / (tan(angle))) / 2;
				}
				if (!raycaster->side) // by y
				{
					if (raycaster->rayX > 0)
						delta = (double) (raycaster->mapX - raycaster->player_x);
					else
						delta = (double) (raycaster->mapX - raycaster->player_x + 1);
					vec = (raycaster->player_y + (delta) * (tan(angle))) / 2;
				}
				printf("vec is %f\n", delta);
				vec = vec - (int) vec;
				if (vec > cub3d->door_open)
					raycaster->hit = TRUE;
				raycaster->door = TRUE;
			}
			if (cub3d->mini_map[backY][backX] == 'D' && backS != raycaster->side)
				help = TRUE;
		}
		if (raycaster->mapX <= 0 || raycaster->mapY <= 0
			|| raycaster->mapY / 2 > (int) cub3d->raycaster.rows_count
			|| raycaster->mapX / 2 > (int) cub3d->mini_map_line_len[raycaster->mapY / 2]
			|| cub3d->mini_map[raycaster->mapY / 2][raycaster->mapX / 2] == '1')
		{
			raycaster->hit = TRUE;
		}
		backX = raycaster->mapX / 2;
		backY = raycaster->mapY / 2;
		backS = raycaster->side;
	}
}

void	cast_rays(t_cub3d *cub3d)
{
	size_t	i;
	double	projected_ray;
	t_raycaster_data	*raycaster;

	raycaster = &cub3d->raycaster;
	raycaster->player_x = 2 * raycaster->player_x;
	raycaster->player_y = 2 * raycaster->player_y;
	i = 0;
	printf("__________________________________\n");
	while (i < WINDOW_WIDTH)
	{
		raycaster->door = FALSE;
		raycaster->hit = FALSE;
		projected_ray = ((2 * i) / (double) WINDOW_WIDTH) - 1;
		raycaster->rayX = raycaster->direction_x + raycaster->camera_x * projected_ray;
		raycaster->rayY = raycaster->direction_y + raycaster->camera_y * projected_ray;
		raycaster->mapX = raycaster->player_x;
		raycaster->mapY = raycaster->player_y;
		raycaster->deltadistX = raycaster->rayX == 0.0 ? DBL_MAX : ft_abs((double) 1 / raycaster->rayX);
		raycaster->deltadistY = raycaster->rayY == 0.0 ? DBL_MAX : ft_abs((double) 1 / raycaster->rayY);
		set_ray_step(cub3d);
		perform_dda(cub3d);
		if (!raycaster->side)
			raycaster->perpwallDist = raycaster->sideDistX - raycaster->deltadistX;
		else
			raycaster->perpwallDist = raycaster->sideDistY - raycaster->deltadistY;
		raycaster->perpwallDist /= 2;
		if (raycaster->perpwallDist < 0.1)
			raycaster->perpwallDist = 0.1;
		cub3d->Zbuffer[i] = raycaster->perpwallDist;
		draw_wall(cub3d, i);
		i++;
	}
	raycaster->player_x = raycaster->player_x / 2;
	raycaster->player_y = raycaster->player_y / 2;
	draw_sprites(cub3d);
}


void	draw_cub3d(t_cub3d *cub3d)
{
	cub3d_window_init(cub3d);
	cub3d_frame_init(cub3d);
	cast_floor(cub3d);
	cast_rays(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->frame.img, 0, 0);
}
