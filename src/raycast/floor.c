/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:05:05 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/18 20:47:21 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_floor(t_cub3d *cub3d)
{
	size_t	rows;
	size_t	columns;
	int		floor_color;
	int		ceiling_color;

	rows = 0;
	floor_color = ((cub3d->texture.floor.r << 16)
			+ (cub3d->texture.floor.g << 8) + cub3d->texture.floor.b);
	ceiling_color = ((cub3d->texture.ceiling.r << 16)
			+ (cub3d->texture.ceiling.g << 8) + cub3d->texture.ceiling.b);
	while (rows < WINDOW_HEIGHT)
	{
		columns = 0;
		while (columns < WINDOW_WIDTH)
		{
			cub3d_pixel_put(cub3d, columns, rows, floor_color);
			cub3d_pixel_put(cub3d, columns, WINDOW_HEIGHT - rows - 1,
				ceiling_color);
			columns++;
		}
		rows++;
	}
}
