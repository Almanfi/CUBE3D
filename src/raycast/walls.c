/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:46:53 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/04 12:07:26 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	calculate_text_x(t_raycaster_data *raycaster, int line_height)
{
	raycaster->wallX = raycaster->player_x / 2
		+ raycaster->perpwallDist * raycaster->rayX;
	if (!raycaster->side)
		raycaster->wallX = raycaster->player_y / 2
			+ raycaster->perpwallDist * raycaster->rayY;
	raycaster->wallX -= floor(raycaster->wallX);
	raycaster->texX = (int)(raycaster->wallX * (double) TEX_DIMENSIONS);
	if (!raycaster->side && raycaster->rayX > 0)
		raycaster->texX = TEX_DIMENSIONS - raycaster->texX - 1;
	else if (raycaster->side && raycaster->rayY < 0)
		raycaster->texX = TEX_DIMENSIONS - raycaster->texX - 1;
	raycaster->tex_step = 1.0 * TEX_DIMENSIONS / line_height;
	raycaster->tex_pos = (raycaster->draw_start - WINDOW_HEIGHT / 2
			+ line_height / 2) * raycaster->tex_step;
}

static	int	get_direction(t_raycaster_data *raycaster)
{
	int	direction;

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
	return (direction);
}

static	void	find_texture_id_and_offset(t_cub3d *cub3d,
					t_raycaster_data *raycaster, int *texture_id)
{
	float	door_open_ratio;
	int		motion_direction;
	int		direction;

	direction = get_direction(raycaster);
	if (direction == NORTH || direction == WEST)
		motion_direction = -1;
	else
		motion_direction = +1;
	if (raycaster->door
		&& is_open_door(cub3d->door, raycaster->mapX / 2,
			raycaster->mapY / 2, &door_open_ratio))
	{
		raycaster->texX += door_open_ratio * TEX_DIMENSIONS * motion_direction;
		*texture_id = DOOR;
	}
	else if (raycaster->door_side)
		*texture_id = DOOR;
	else
		*texture_id = direction;
}

static	void	draw_textured_wall(t_cub3d *cub3d, size_t x, int line_height)
{
	t_raycaster_data	*raycaster;
	int					id;
	int					y;

	raycaster = &cub3d->raycaster;
	calculate_text_x(raycaster, line_height);
	find_texture_id_and_offset(cub3d, raycaster, &id);
	y = raycaster->draw_start;
	while (y < raycaster->draw_end)
	{
		raycaster->texY = (int) raycaster->tex_pos & (TEX_DIMENSIONS - 1);
		raycaster->tex_pos += raycaster->tex_step;
		cub3d_pixel_put(cub3d, x, y, cub3d->texture
			.tx[id][TEX_DIMENSIONS * raycaster->texY + raycaster->texX]);
		y++;
	}
}

void	draw_wall(t_cub3d *cub3d, size_t x)
{
	t_raycaster_data	*raycaster;
	int					line_height;

	raycaster = &cub3d->raycaster;
	line_height = WINDOW_HEIGHT;
	if (raycaster->perpwallDist > 0.01)
		line_height = (int )(WINDOW_HEIGHT / raycaster->perpwallDist);
	raycaster->draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (raycaster->draw_start < 0)
		raycaster->draw_start = 0;
	raycaster->draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (raycaster->draw_end >= WINDOW_HEIGHT)
		raycaster->draw_end = WINDOW_HEIGHT - 1;
	draw_textured_wall(cub3d, x, line_height);
}
