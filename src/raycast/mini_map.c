/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:50:05 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/06 17:53:19 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	t_boolean	check_map(int x, int y, t_cub3d *cub3d, int *color)
{
	float	xm;
	float	ym;
	int		ratio;

	ratio = cub3d->minimap.unit;
	xm = (float )(x - (cub3d->minimap.width) / 2) / ratio
		+ cub3d->raycaster.player_x;
	ym = (float )(y - (cub3d->minimap.height) / 2) / ratio
		+ cub3d->raycaster.player_y;
	if (ym >= 0 && ym < (int) cub3d->raycaster.rows_count
		&& xm >= 0 && xm < (int) cub3d->mini_map_line_len[(int) ym]
		&& ft_strchr("0D", cub3d->mini_map[(int) ym][(int) xm]))
	{
		if (cub3d->mini_map[(int) ym][(int) xm] == '0')
			*color = 0xffffff;
		else
			*color = 0x00ff00;
		return (TRUE);
	}
	else
		return (FALSE);
}

static	void	draw_mini_map_fov(t_cub3d *cub3d)
{
	t_raycaster_data	*raycaster;
	t_projected_point	start;
	t_projected_point	end;
	int					length;

	length = 500;
	raycaster = &cub3d->raycaster;
	start.x = cub3d->minimap.width / 2;
	start.y = cub3d->minimap.height / 2;
	end.x = start.x + length * (raycaster->direction_x * 100
			+ raycaster->camera_x * 102);
	end.y = start.y + length * (raycaster->direction_y * 100
			+ raycaster->camera_y * 102);
	cub3d_draw_line(cub3d, start, end);
	end.x = start.x + length * (raycaster->direction_x * 100
			- raycaster->camera_x * 102);
	end.y = start.y + length * (raycaster->direction_y * 100
			- raycaster->camera_y * 102);
	cub3d_draw_line(cub3d, start, end);
}

static	t_boolean	draw_minimap_object(t_cub3d *cub3d, int x, int y)
{
	int	color;

	if (y > (cub3d->minimap.height - cub3d->minimap.unit) / 2
		&& y < (cub3d->minimap.height + cub3d->minimap.unit) / 2
		&& x > (cub3d->minimap.width - cub3d->minimap.unit) / 2
		&& x < (cub3d->minimap.width + cub3d->minimap.unit) / 2)
		cub3d_pixel_put(cub3d, x, y, 0xff0000);
	else if (check_map(x, y, cub3d, &color))
		cub3d_pixel_put(cub3d, x, y, color);
	else
		return (FALSE);
	return (TRUE);
}

void	draw_minimap(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub3d->minimap.height)
	{
		x = 0;
		while (x < cub3d->minimap.width)
		{
			if (draw_minimap_object(cub3d, x, y))
				;
			else if (x < 2 || x > cub3d->minimap.width - 3
				|| y < 2 || y > cub3d->minimap.height - 3)
				cub3d_pixel_put(cub3d, x, y, 0xaaaaaa);
			else
				cub3d_pixel_put(cub3d, x, y, 0x000000);
			x++;
		}
		y++;
	}
	draw_mini_map_fov(cub3d);
}
