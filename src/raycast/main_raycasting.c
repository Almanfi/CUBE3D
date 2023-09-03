/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:46:29 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/03 21:59:48 by maboulkh         ###   ########.fr       */
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

static void init_ray(t_raycaster_data *raycaster, size_t i)
{
	double	projected_ray;

	raycaster->door = FALSE;
	raycaster->hit = FALSE;
	projected_ray = ((2 * i) / (double) WINDOW_WIDTH) - 1;
	raycaster->rayX = raycaster->direction_x + raycaster->camera_x * projected_ray;
	raycaster->rayY = raycaster->direction_y + raycaster->camera_y * projected_ray;
	raycaster->mapX = raycaster->player_x;
	raycaster->mapY = raycaster->player_y;
	raycaster->deltadistX = raycaster->rayX == 0.0 ? DBL_MAX : ft_abs((double) 1 / raycaster->rayX);
	raycaster->deltadistY = raycaster->rayY == 0.0 ? DBL_MAX : ft_abs((double) 1 / raycaster->rayY);
}

void	cast_rays(t_cub3d *cub3d)
{
	t_raycaster_data	*raycaster;
	size_t				i;

	raycaster = &cub3d->raycaster;
	raycaster->player_x = 2 * raycaster->player_x;
	raycaster->player_y = 2 * raycaster->player_y;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		init_ray(raycaster, i);
		set_ray_step(cub3d);
		perform_dda(cub3d);
		if (!raycaster->side)
			raycaster->perpwallDist = raycaster->sideDistX - raycaster->deltadistX;
		else
			raycaster->perpwallDist = raycaster->sideDistY - raycaster->deltadistY;
		raycaster->perpwallDist /= 2;
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
