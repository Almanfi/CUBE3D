/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:44:11 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/11 09:48:04 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void draw_textured_wall(t_cub3d *cub3d, size_t x, int line_height)
{
	t_raycaster_data *raycaster;
	int				 y;

	raycaster = &cub3d->raycaster;
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
	while (y < raycaster->draw_end)
	{
		raycaster->texY = (int) raycaster->tex_pos & (TEX_DIMENSIONS - 1);
		raycaster->tex_pos +=  raycaster->tex_step;
		cub3d_pixel_put(cub3d, x, y, cub3d->texture.r_textures[0][TEX_DIMENSIONS * raycaster->texY + raycaster->texX]);
		y++;
	}
}

void draw_wall(t_cub3d *cub3d, size_t x)
{
	int line_height;
	t_raycaster_data *raycaster;

	raycaster = &cub3d->raycaster;
	line_height = (int) (WINDOW_HEIGHT / raycaster->perpwallDist);
	raycaster->draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (raycaster->draw_start < 0)
		raycaster->draw_start = 0;
	raycaster->draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (raycaster->draw_end >= WINDOW_HEIGHT)
		raycaster->draw_end = WINDOW_HEIGHT - 1;
	draw_textured_wall(cub3d, x, line_height);
}

