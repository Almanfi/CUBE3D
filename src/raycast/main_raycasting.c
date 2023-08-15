/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:31:04 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/15 16:31:42 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <float.h>

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

	raycaster = &cub3d->raycaster;
	while (!raycaster->hit)
	{
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
		if (raycaster->mapX <= 0 || raycaster->mapY <= 0 || 
			raycaster->mapY > (int) cub3d->raycaster.rows_count || 
			raycaster->mapX > (int) cub3d->mini_map_line_len[raycaster->mapY]
			||cub3d->mini_map[raycaster->mapY][raycaster->mapX] == '1')
			raycaster->hit = TRUE;
	}
}


void	cast_rays(t_cub3d *cub3d)
{
	size_t	i;
	double	projected_ray;
	t_raycaster_data	*raycaster;

	raycaster = &cub3d->raycaster;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		raycaster->hit = FALSE;
		projected_ray = ((2 * i) / (double) WINDOW_WIDTH) - 1;
		raycaster->rayX = raycaster->direction_x + raycaster->camera_x * projected_ray;
		raycaster->rayY = raycaster->direction_y + raycaster->camera_y * projected_ray;
		raycaster->mapX = raycaster->player_x;
		raycaster->mapY = raycaster->player_y;
		raycaster->deltadistX = raycaster->rayX == 0.0 ? DBL_MAX : ft_abs((double) 1 / raycaster->rayX);
		raycaster->deltadistY = raycaster->rayY == 0.0 ? DBL_MAX : ft_abs((double) 1 / raycaster->rayY);
		set_ray_step(cub3d);
	// printf("inside\n");
		perform_dda(cub3d);
	// printf("before draw\n");
		if (!raycaster->side)
			raycaster->perpwallDist = raycaster->sideDistX - raycaster->deltadistX;
		else
			raycaster->perpwallDist = raycaster->sideDistY - raycaster->deltadistY;
		draw_wall(cub3d, i);
		i++;
	}
}

void	draw_cub3d(t_cub3d *cub3d)
{
	cub3d_window_init(cub3d);
	cub3d_frame_init(cub3d);
	cast_rays(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->frame.img, 0, 0);
}

