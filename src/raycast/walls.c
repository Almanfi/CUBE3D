/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:46:53 by maboulkh          #+#    #+#             */
/*   Updated: 2023/08/23 23:01:23 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void draw_textured_wall(t_cub3d *cub3d, size_t x, int line_height)
{
	t_raycaster_data 	*raycaster;
	int				 	y;
	int					direction;

	raycaster = &cub3d->raycaster;
	if (!raycaster->side)
	{
		if (raycaster->rayX > 0)
			direction = EAST;
		else
			direction = WEST;
	}
	else
	{
		if (raycaster->rayY > 0)
			direction = NORTH;
		else
			direction = SOUTH;
	}
	raycaster->wallX = raycaster->player_x + raycaster->perpwallDist * raycaster->rayX;
	if (!raycaster->side)
		raycaster->wallX = raycaster->player_y + raycaster->perpwallDist * raycaster->rayY;
	raycaster->wallX -= floor(raycaster->wallX);
	raycaster->texX = (int)(raycaster->wallX * (double) TEX_DIMENSIONS);
	if (!raycaster->side && raycaster->rayX > 0)
		raycaster->texX = TEX_DIMENSIONS - raycaster->texX - 1;
	else if (raycaster->side && raycaster->rayY < 0)
		raycaster->texX = TEX_DIMENSIONS - raycaster->texX - 1;
	raycaster->tex_step = 1.0 * TEX_DIMENSIONS / line_height;
	raycaster->tex_pos = (raycaster->draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * raycaster->tex_step;
	y = raycaster->draw_start;
	if (raycaster->door)
		direction = DOOR;
		// printf("drawing door txtr\n");
	while (y < raycaster->draw_end)
	{
		// if (y > raycaster->draw_end / 2)
		// 	dire
		raycaster->texY = (int) raycaster->tex_pos & (TEX_DIMENSIONS - 1);
		raycaster->tex_pos +=  raycaster->tex_step;
		cub3d_pixel_put(cub3d, x, y, cub3d->texture.tx[direction][TEX_DIMENSIONS * raycaster->texY + raycaster->texX]);
		y++;
	}
}

void draw_wall(t_cub3d *cub3d, size_t x)
{
	int line_height;
	t_raycaster_data *raycaster;

	raycaster = &cub3d->raycaster;
	// if (raycaster->door)
	// 	raycaster->perpwallDist += 0.5;
	line_height = WINDOW_HEIGHT;
	if (raycaster->perpwallDist > 0.01)
		line_height = (int) (WINDOW_HEIGHT / raycaster->perpwallDist);
	raycaster->draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (raycaster->draw_start < 0)
		raycaster->draw_start = 0;
	raycaster->draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (raycaster->draw_end >= WINDOW_HEIGHT)
		raycaster->draw_end = WINDOW_HEIGHT - 1;
	draw_textured_wall(cub3d, x, line_height);
}

