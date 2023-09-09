/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:46:53 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/09 15:50:21 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	calculate_text_x(t_raycaster_data *raycaster, int line_height)
{
	raycaster->wall_x = raycaster->player_x / 2
		+ raycaster->perpwalldist * raycaster->ray_x;
	if (!raycaster->side)
		raycaster->wall_x = raycaster->player_y / 2
			+ raycaster->perpwalldist * raycaster->ray_y;
	raycaster->wall_x -= floor(raycaster->wall_x);
	raycaster->tex_x = (int)(raycaster->wall_x * (double) TEX_DIMENSIONS);
	if (!raycaster->side && raycaster->ray_x > 0)
		raycaster->tex_x = TEX_DIMENSIONS - raycaster->tex_x - 1;
	else if (raycaster->side && raycaster->ray_y < 0)
		raycaster->tex_x = TEX_DIMENSIONS - raycaster->tex_x - 1;
	raycaster->tex_step = 1.0 * TEX_DIMENSIONS / line_height;
	raycaster->tex_pos = (raycaster->draw_start - WINDOW_HEIGHT / 2
			+ line_height / 2) * raycaster->tex_step;
}

static	int	get_direction(t_raycaster_data *raycaster)
{
	int	direction;

	if (!raycaster->side)
	{
		if (raycaster->ray_x > 0)
			direction = EAST;
		else
			direction = WEST;
	}
	else
	{
		if (raycaster->ray_y > 0)
			direction = SOUTH;
		else
			direction = NORTH;
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
		&& is_open_door(cub3d->door, raycaster->map_x / 2,
			raycaster->map_y / 2, &door_open_ratio))
	{
		raycaster->tex_x += door_open_ratio * TEX_DIMENSIONS * motion_direction;
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
		raycaster->tex_y = (int) raycaster->tex_pos & (TEX_DIMENSIONS - 1);
		raycaster->tex_pos += raycaster->tex_step;
		cub3d_pixel_put(cub3d, x, y, cub3d->texture
			.tx[id][TEX_DIMENSIONS * raycaster->tex_y + raycaster->tex_x]);
		y++;
	}
}

void	draw_wall(t_cub3d *cub3d, size_t x)
{
	t_raycaster_data	*raycaster;
	int					line_height;

	raycaster = &cub3d->raycaster;
	line_height = WINDOW_HEIGHT;
	if (raycaster->perpwalldist > 0.01)
		line_height = (int )(WINDOW_HEIGHT / raycaster->perpwalldist);
	raycaster->draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (raycaster->draw_start < 0)
		raycaster->draw_start = 0;
	raycaster->draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (raycaster->draw_end >= WINDOW_HEIGHT)
		raycaster->draw_end = WINDOW_HEIGHT - 1;
	draw_textured_wall(cub3d, x, line_height);
}
