/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:36:11 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/03 17:00:24 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	t_boolean	check_sprite_collision(t_cub3d *cub3d, double x, double y)
{
	size_t	i;
	double	sprite_half_width;

	sprite_half_width = 0.3;
	i = 0;
	while (i < cub3d->sprite_count)
	{
		if (x >= cub3d->sprites[i]->x - sprite_half_width
			&& x <= cub3d->sprites[i]->x + sprite_half_width
			&& y >= cub3d->sprites[i]->y - sprite_half_width
			&& y <= cub3d->sprites[i]->y + sprite_half_width)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_boolean	is_not_traversable(t_cub3d *cub3d, int x, int y)
{
	float	door_open_ratio;

	if (cub3d->mini_map[x][y] == '0' || (cub3d->mini_map[x][y] == 'D'
		&& is_open_door(cub3d->door, y, x, &door_open_ratio)
		&& door_open_ratio > 1))
		return (FALSE);
	return (TRUE);
}

static	t_boolean	check_surounding(t_cub3d *cub3d, double xp, double yp)
{
	double	step;
	double	x;
	double	y;

	step = HB_RADIUS;
	x = xp - step;
	while (x <= xp + step)
	{
		y = yp - step;
		while (y <= yp + step)
		{
			if (is_not_traversable(cub3d, x, y))
				return (FALSE);
			y += step;
		}
		x += step;
	}
	return (TRUE);
}

void	move_player(t_cub3d *cub3d)
{
	t_raycaster_data	*raycaster;
	float				move_speed;
	double				x;
	double				y;

	move_speed = 0.2;
	raycaster = &cub3d->raycaster;
	y = raycaster->player_x + move_speed
		* (cub3d->move_vertical * raycaster->direction_x
			+ cub3d->move_horizontal * raycaster->camera_x);
	x = raycaster->player_y;
	if (check_surounding(cub3d, x, y) && check_sprite_collision(cub3d, y, x))
		raycaster->player_x = y;
	y = raycaster->player_x;
	x = raycaster->player_y + move_speed
		* (cub3d->move_vertical * raycaster->direction_y
			+ cub3d->move_horizontal * raycaster->camera_y);
	if (check_surounding(cub3d, x, y) && check_sprite_collision(cub3d, y, x))
		raycaster->player_y = x;
}

void	rotate_player(t_cub3d *cub3d)
{
	t_raycaster_data	*raycaster;
	double				old_direction_x;
	double				old_camera_x;
	double				rot_speed;
	double				rot_const;

	rot_const = 0.08;
	raycaster = &cub3d->raycaster;
	rot_speed = cub3d->rotation_dir * rot_const;
	old_direction_x = raycaster->direction_x;
	old_camera_x = raycaster->camera_x;
	raycaster->direction_x = old_direction_x * cos(rot_speed)
		- raycaster->direction_y * sin(rot_speed);
	raycaster->direction_y = old_direction_x * sin(rot_speed)
		+ raycaster->direction_y * cos(rot_speed);
	raycaster->camera_x = old_camera_x * cos(rot_speed)
		- raycaster->camera_y * sin(rot_speed);
	raycaster->camera_y = old_camera_x * sin(rot_speed)
		+ raycaster->camera_y * cos(rot_speed);
}
