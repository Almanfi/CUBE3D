/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:28:35 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/06 17:34:31 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	find_transform_vector(t_cub3d *cub3d, 
	t_raycaster_data *rc, int id)
{
	rc->sprite_x = cub3d->sprites[id]->x - rc->player_x;
	rc->sprite_y = cub3d->sprites[id]->y - rc->player_y;
	rc->inv_Det = 1.0 / (rc->camera_x * rc->direction_y
			- rc->direction_x * rc->camera_y);
	rc->transform_X = rc->inv_Det * (rc->direction_y * rc->sprite_x 
			- rc->direction_x * rc->sprite_y);
	rc->transform_Y = rc->inv_Det * ((-rc->camera_y) * rc->sprite_x
			+ rc->camera_x * rc->sprite_y);
}

static	void	find_sprite_corners(t_raycaster_data *rc)
{
	rc->sprite_screenX = (int )((WINDOW_WIDTH / 2) 
			* (1 + rc->transform_X / rc->transform_Y));
	rc->sprite_height = ft_abs((int) WINDOW_HEIGHT / rc->transform_Y);
	rc->draw_startY = -rc->sprite_height / 2 + WINDOW_HEIGHT / 2;
	if (rc->draw_startY < 0)
		rc->draw_startY = 0;
	rc->draw_endY = rc->sprite_height / 2 + WINDOW_HEIGHT / 2;
	if (rc->draw_startY >= WINDOW_HEIGHT)
		rc->draw_endY = WINDOW_HEIGHT - 1;
	rc->sprite_width = ft_abs((int) WINDOW_HEIGHT / rc->transform_Y);
	rc->draw_startX = -rc->sprite_width / 2 + rc->sprite_screenX;
	if (rc->draw_startX < 0)
		rc->draw_startX = 0;
	rc->draw_endX = rc->sprite_width / 2 + rc->sprite_screenX;
	if (rc->draw_endX >= WINDOW_WIDTH)
		rc->draw_endX = WINDOW_WIDTH - 1;
}

static	void	draw_stripe(t_cub3d *cub3d, t_raycaster_data *rc, int stripe)
{
	int		row;
	int		tex_d;
	int		pos;

	rc->texX = ((int )((stripe - (-rc->sprite_width / 2 + rc->sprite_screenX))
				* TEX_DIMENSIONS / rc->sprite_width));
	if (rc->transform_Y > 0 && stripe > 0
		&& stripe < WINDOW_WIDTH && rc->transform_Y < cub3d->Zbuffer[stripe])
	{
		row = rc->draw_startY;
		while (row < rc->draw_endY)
		{
			tex_d = 256 * (row - WINDOW_HEIGHT / 2 + rc->sprite_height / 2);
			rc->texY = ((tex_d * TEX_DIMENSIONS) / rc-> sprite_height) / 256;
			pos = TEX_DIMENSIONS * rc->texY + rc->texX;
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
		stripe = rc->draw_startX - 1;
		while (++stripe < rc->draw_endX)
			draw_stripe(cub3d, rc, stripe);
	}
}
