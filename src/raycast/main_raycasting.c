/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:46:29 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/04 13:19:29 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	set_ray_step(t_cub3d *cub3d)
{
	t_raycaster_data	*r_c;

	r_c = &cub3d->raycaster;
	if (r_c->rayX < 0)
	{
		r_c->step_x = -1;
		r_c->sideDistX = (r_c->player_x - r_c->mapX) * r_c->deltadistX;
	}
	else
	{
		r_c->step_x = 1;
		r_c->sideDistX = (r_c->mapX + 1.0 - r_c->player_x) * r_c->deltadistX;
	}
	if (r_c->rayY < 0)
	{
		r_c->step_y = -1;
		r_c->sideDistY = (r_c->player_y - r_c->mapY) * r_c->deltadistY;
	}
	else
	{
		r_c->step_y = 1;
		r_c->sideDistY = (r_c->mapY + 1.0 - r_c->player_y) * r_c->deltadistY;
	}
}

static	void	init_ray(t_raycaster_data *r_c, size_t i)
{
	double	projected_ray;

	r_c->door = FALSE;
	r_c->hit = FALSE;
	projected_ray = ((2 * i) / (double) WINDOW_WIDTH) - 1;
	r_c->rayX = r_c->direction_x + r_c->camera_x * projected_ray;
	r_c->rayY = r_c->direction_y + r_c->camera_y * projected_ray;
	r_c->mapX = r_c->player_x;
	r_c->mapY = r_c->player_y;
	if (r_c->rayX == 0.0)
		r_c->deltadistX = DBL_MAX;
	else
		r_c->deltadistX = ft_abs((double) 1 / r_c->rayX);
	if (r_c->rayY == 0.0)
		r_c->deltadistY = DBL_MAX;
	else
		r_c->deltadistY = ft_abs((double) 1 / r_c->rayY);
}

void	cast_rays(t_cub3d *cub3d)
{
	t_raycaster_data	*r_c;
	size_t				i;

	r_c = &cub3d->raycaster;
	r_c->player_x = 2 * r_c->player_x;
	r_c->player_y = 2 * r_c->player_y;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		init_ray(r_c, i);
		set_ray_step(cub3d);
		perform_dda(cub3d);
		if (!r_c->side)
			r_c->perpwallDist = r_c->sideDistX - r_c->deltadistX;
		else
			r_c->perpwallDist = r_c->sideDistY - r_c->deltadistY;
		r_c->perpwallDist /= 2;
		cub3d->Zbuffer[i] = r_c->perpwallDist;
		draw_wall(cub3d, i);
		i++;
	}
	r_c->player_x = r_c->player_x / 2;
	r_c->player_y = r_c->player_y / 2;
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
