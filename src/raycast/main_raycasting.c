/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:46:29 by maboulkh          #+#    #+#             */
/*   Updated: 2023/08/21 18:36:13 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"
#include <float.h>

static void	set_ray_step_for_collision(t_cub3d *cub3d, t_raycaster_data *raycaster)
{
	(void) cub3d;
	if (raycaster->rayX < 0)
	{
		raycaster->step_x = -1;
		raycaster->sideDistX = ((double) raycaster->player_x - raycaster->mapX) * raycaster->deltadistX;
	}
	else
	{
		raycaster->step_x = 1;
		raycaster->sideDistX = ((double) raycaster->mapX + 1.0 - raycaster->player_x) * raycaster->deltadistX;
	}
	if (raycaster->rayY < 0)
	{
		raycaster->step_y = -1;
		raycaster->sideDistY = ((double) raycaster->player_y - raycaster->mapY) * raycaster->deltadistY;
	}
	else
	{
		raycaster->step_y = 1;
		raycaster->sideDistY = ((double) raycaster->mapY + 1.0 - raycaster->player_y) * raycaster->deltadistY;
	}
}

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

static	t_boolean	perform_dda_for_collision(t_cub3d *cub3d, t_raycaster_data *raycaster)
{
	// raycaster = &cub3d->raycaster;
	// while (raycaster->sideDistX <= HB_RADIUS || raycaster->sideDistY <= HB_RADIUS)
	while (!raycaster->hit)
	{
		if (raycaster->sideDistX > 2 && raycaster->sideDistY > 2)
		{
			return (FALSE);
		}
		if (raycaster->mapX <= 0 || raycaster->mapY <= 0 || 
			raycaster->mapY > (int) cub3d->raycaster.rows_count || 
			raycaster->mapX > (int) cub3d->mini_map_line_len[raycaster->mapY]
			||cub3d->mini_map[raycaster->mapY][raycaster->mapX] == '1')
		{
			if (raycaster->sideDistX < 0.5 || raycaster->sideDistY < 0.5)
			{
				printf("distX = %lf, distY = %lf\n", raycaster->sideDistX, raycaster->sideDistY);
				printf("got a collision\n");
				return (TRUE);
			}
			else
				return (FALSE);
		}
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
		// if (raycaster->mapX <= 0 || raycaster->mapY <= 0 || 
		// 	raycaster->mapY > (int) cub3d->raycaster.rows_count || 
		// 	raycaster->mapX > (int) cub3d->mini_map_line_len[raycaster->mapY]
		// 	||cub3d->mini_map[raycaster->mapY][raycaster->mapX] == '1')
		// 	raycaster->hit = TRUE;
	}
	return (FALSE);
}

t_boolean	cast_rays_for_collision(t_cub3d *cub3d, double x, double y)
{
	double alpha;
	t_raycaster_data	*raycaster;
	t_raycaster_data	raycaster_data;


	raycaster_data = cub3d->raycaster;
	raycaster = &raycaster_data;
	alpha = 0.0;
	raycaster->player_x = y;
	raycaster->player_y = x;
	// printf("RC player at x = %lf, y = %lf\n", x, y);
	while (alpha < M_PI * 2)
	{
		raycaster->hit = FALSE;
		raycaster->rayX = cos(alpha);
		raycaster->rayY = sin(alpha);
		raycaster->mapX = raycaster->player_x;
		raycaster->mapY = raycaster->player_y;
		raycaster->deltadistX = raycaster->rayX == 0.0 ? DBL_MAX : ft_abs((double) 1 / raycaster->rayX);
		raycaster->deltadistY = raycaster->rayY == 0.0 ? DBL_MAX : ft_abs((double) 1 / raycaster->rayY);
		set_ray_step_for_collision(cub3d, raycaster);
		if (perform_dda_for_collision(cub3d, raycaster))
			return (TRUE);
		// perform_dda_for_collision(cub3d, raycaster);
		// if (!raycaster->side)
		// {
		// 	if (alpha < M_PI)
		// 		raycaster->perpwallDist = raycaster->sideDistX;
		// 	else
		// 		raycaster->perpwallDist = raycaster->sideDistX - raycaster->deltadistX;
				
		// }
		// else
		// 	raycaster->perpwallDist = raycaster->sideDistY - raycaster->deltadistY;
		// if (raycaster->perpwallDist < 0.1)
		// {
		// 	printf("TRUE : collision at angle %lf, with dist %lf\n", alpha * 180 / M_PI, raycaster->perpwallDist);
		// 	return (TRUE);
		// }
		// printf("RC distXY at x = %lf, y = %lf\n", raycaster->deltadistX, raycaster->deltadistY);
		alpha += M_PI / 18;
	}
	// printf("FALSE1\n");
	return (FALSE);
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
		perform_dda(cub3d);
		if (!raycaster->side)
			raycaster->perpwallDist = raycaster->sideDistX - raycaster->deltadistX;
		else
			raycaster->perpwallDist = raycaster->sideDistY - raycaster->deltadistY;
		cub3d->Zbuffer[i] = raycaster->perpwallDist;
		draw_wall(cub3d, i);
		i++;
	}
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
