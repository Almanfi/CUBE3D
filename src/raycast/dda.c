/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:58:50 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/09 14:34:02 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static	void	make_dda_backup(t_raycaster_data *raycaster)
{
	raycaster->back_x = raycaster->map_x / 2;
	raycaster->back_y = raycaster->map_y / 2;
	raycaster->back_s = raycaster->side;
}

static	void	calculate_next_increment(t_raycaster_data *raycaster)
{
	if (raycaster->sidedist_x < raycaster->sidedist_y)
	{
		raycaster->sidedist_x += raycaster->deltadist_x;
		raycaster->map_x += raycaster->step_x;
		raycaster->side = FALSE;
	}
	else
	{
		raycaster->sidedist_y += raycaster->deltadist_y;
		raycaster->map_y += raycaster->step_y;
		raycaster->side = TRUE;
	}
}

static	double	calculate_door_intersection_ratio(t_raycaster_data *raycaster)
{
	double	intersection;

	intersection = 1;
	if (raycaster->side)
	{
		if (raycaster->ray_y > 0)
			raycaster->delta = raycaster->map_y - raycaster->player_y;
		else
			raycaster->delta = raycaster->map_y - raycaster->player_y + 1;
		intersection = (raycaster->player_x + (raycaster->delta)
				/ (tan(raycaster->angle))) / 2;
	}
	if (!raycaster->side)
	{
		if (raycaster->ray_x > 0)
			raycaster->delta = raycaster->map_x - raycaster->player_x;
		else
			raycaster->delta = raycaster->map_x - raycaster->player_x + 1;
		intersection = (raycaster->player_y + (raycaster->delta)
				* (tan(raycaster->angle))) / 2;
	}
	intersection = intersection - (int) intersection;
	return (intersection);
}

static	t_boolean	inside_wall(t_cub3d *cub3d, t_raycaster_data *raycaster)
{
	float	door_open_ratio;

	if (cub3d->mini_map[raycaster->back_y][raycaster->back_x] == 'D'
		&& (raycaster->back_s == raycaster->side || raycaster->pass_door))
	{
		if (is_open_door(cub3d->door, raycaster->map_x / 2,
				raycaster->map_y / 2, &door_open_ratio) == FALSE)
			raycaster->hit = TRUE;
		else if (calculate_door_intersection_ratio(raycaster) > door_open_ratio)
			raycaster->hit = TRUE;
		raycaster->door = TRUE;
	}
	if (cub3d->mini_map[raycaster->back_y][raycaster->back_x] == 'D'
		&& raycaster->back_s != raycaster->side)
		raycaster->pass_door = TRUE;
	else
		raycaster->pass_door = FALSE;
	return (TRUE);
}

void	perform_dda(t_cub3d *cub3d)
{
	t_raycaster_data	*rc;

	rc = &cub3d->raycaster;
	make_dda_backup(rc);
	rc->angle = atan(rc->ray_y / rc->ray_x);
	while (!rc->hit)
	{
		rc->door = FALSE;
		rc->door_side = FALSE;
		if (cub3d->mini_map[rc->map_y / 2][rc->map_x / 2] == 'D')
			rc->door_side = TRUE;
		calculate_next_increment(rc);
		if (rc->map_x <= 0 || rc->map_y <= 0
			|| rc->map_y / 2 > (int) rc->rows_count
			|| rc->map_x / 2 > (int) cub3d->mini_map_line_len[rc->map_y / 2]
			|| cub3d->mini_map[rc->map_y / 2][rc->map_x / 2] == 'D')
			inside_wall(cub3d, rc);
		if (rc->map_x <= 0 || rc->map_y <= 0
			|| rc->map_y / 2 > (int) rc->rows_count
			|| rc->map_x / 2 > (int) cub3d->mini_map_line_len[rc->map_y / 2]
			|| cub3d->mini_map[rc->map_y / 2][rc->map_x / 2] == '1')
			rc->hit = TRUE;
		make_dda_backup(rc);
	}
}
