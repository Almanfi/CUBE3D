/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:46:29 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/09 14:38:24 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_ray_step(t_cub3d *cub3d)
{
	t_raycaster_data	*r_c;

	r_c = &cub3d->raycaster;
	if (r_c->ray_x < 0)
	{
		r_c->step_x = -1;
		r_c->sidedist_x = (r_c->player_x - r_c->map_x) * r_c->deltadist_x;
	}
	else
	{
		r_c->step_x = 1;
		r_c->sidedist_x = (r_c->map_x + 1.0 - r_c->player_x) * r_c->deltadist_x;
	}
	if (r_c->ray_y < 0)
	{
		r_c->step_y = -1;
		r_c->sidedist_y = (r_c->player_y - r_c->map_y) * r_c->deltadist_y;
	}
	else
	{
		r_c->step_y = 1;
		r_c->sidedist_y = (r_c->map_y + 1.0 - r_c->player_y) * r_c->deltadist_y;
	}
}

static void	init_ray(t_raycaster_data *r_c, size_t i)
{
	double	projected_ray;

	r_c->door = FALSE;
	r_c->hit = FALSE;
	projected_ray = ((2 * i) / (double)WINDOW_WIDTH) - 1;
	r_c->ray_x = r_c->direction_x + r_c->camera_x * projected_ray;
	r_c->ray_y = r_c->direction_y + r_c->camera_y * projected_ray;
	r_c->map_x = r_c->player_x;
	r_c->map_y = r_c->player_y;
	if (r_c->ray_x == 0.0)
		r_c->deltadist_x = DBL_MAX;
	else
		r_c->deltadist_x = ft_abs((double)1 / r_c->ray_x);
	if (r_c->ray_y == 0.0)
		r_c->deltadist_y = DBL_MAX;
	else
		r_c->deltadist_y = ft_abs((double)1 / r_c->ray_y);
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
			r_c->perpwalldist = r_c->sidedist_x - r_c->deltadist_x;
		else
			r_c->perpwalldist = r_c->sidedist_y - r_c->deltadist_y;
		r_c->perpwalldist /= 2;
		cub3d->zbuffer[i] = r_c->perpwalldist;
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
