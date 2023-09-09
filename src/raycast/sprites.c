/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:28:35 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/09 14:38:24 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	find_transform_vector(t_cub3d *cub3d, 
	t_raycaster_data *rc, int id)
{
	rc->sprite_x = cub3d->sprites[id]->x - rc->player_x;
	rc->sprite_y = cub3d->sprites[id]->y - rc->player_y;
	rc->inv_det = 1.0 / (rc->camera_x * rc->direction_y
			- rc->direction_x * rc->camera_y);
	rc->transform_x = rc->inv_det * (rc->direction_y * rc->sprite_x 
			- rc->direction_x * rc->sprite_y);
	rc->transform_y = rc->inv_det * ((-rc->camera_y) * rc->sprite_x
			+ rc->camera_x * rc->sprite_y);
}

static	void	find_sprite_corners(t_raycaster_data *rc)
{
	rc->sprite_screenx = (int )((WINDOW_WIDTH / 2) 
			* (1 + rc->transform_x / rc->transform_y));
	rc->sprite_height = ft_abs((int) WINDOW_HEIGHT / rc->transform_y);
	rc->draw_starty = -rc->sprite_height / 2 + WINDOW_HEIGHT / 2;
	if (rc->draw_starty < 0)
		rc->draw_starty = 0;
	rc->draw_endy = rc->sprite_height / 2 + WINDOW_HEIGHT / 2;
	if (rc->draw_starty >= WINDOW_HEIGHT)
		rc->draw_endy = WINDOW_HEIGHT - 1;
	rc->sprite_width = ft_abs((int) WINDOW_HEIGHT / rc->transform_y);
	rc->draw_startx = -rc->sprite_width / 2 + rc->sprite_screenx;
	if (rc->draw_startx < 0)
		rc->draw_startx = 0;
	rc->draw_endx = rc->sprite_width / 2 + rc->sprite_screenx;
	if (rc->draw_endx >= WINDOW_WIDTH)
		rc->draw_endx = WINDOW_WIDTH - 1;
}

static	void	draw_stripe(t_cub3d *cub3d, t_raycaster_data *rc, int stripe)
{
	int		row;
	int		tex_d;
	int		pos;

	rc->tex_x = ((int )((stripe - (-rc->sprite_width / 2 + rc->sprite_screenx))
				* TEX_DIMENSIONS / rc->sprite_width));
	if (rc->transform_y > 0 && stripe > 0
		&& stripe < WINDOW_WIDTH && rc->transform_y < cub3d->zbuffer[stripe])
	{
		row = rc->draw_starty;
		while (row < rc->draw_endy)
		{
			tex_d = 256 * (row - WINDOW_HEIGHT / 2 + rc->sprite_height / 2);
			rc->tex_y = ((tex_d * TEX_DIMENSIONS) / rc-> sprite_height) / 256;
			pos = TEX_DIMENSIONS * rc->tex_y + rc->tex_x;
			if ((cub3d->texture.tx[FIREHEAD1 + cub3d->texturen][pos]
				& 0x00FFFFFF) != 0)
				cub3d_pixel_put(cub3d, stripe, row,
					cub3d->texture.tx[FIREHEAD1 + cub3d->texturen][pos]);
			row++;
		}
	}
}

static	void	calculate_sprite_distance(t_sprite **sprites,
	t_raycaster_data *r_c)
{
	double	dx;
	double	dy;

	while (sprites && *sprites)
	{
		dx = r_c->player_x - (*sprites)->x;
		dy = r_c->player_y - (*sprites)->y;
		(*sprites)->distance = dx * dx + dy * dy;
		sprites++;
	}
}

void	draw_sprites(t_cub3d *cub3d)
{
	t_raycaster_data	*rc;
	int					stripe;
	size_t				i;

	rc = &cub3d->raycaster;
	calculate_sprite_distance(cub3d->sprites, &(cub3d->raycaster));
	rev_sort_sprites(cub3d->sprites);
	i = -1;
	while (++i < cub3d->sprite_count)
	{
		find_transform_vector(cub3d, rc, i);
		find_sprite_corners(rc);
		stripe = rc->draw_startx - 1;
		while (++stripe < rc->draw_endx)
			draw_stripe(cub3d, rc, stripe);
	}
}
