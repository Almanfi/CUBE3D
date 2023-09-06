/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:58:50 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/06 17:24:57 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static	void	make_dda_backup(t_raycaster_data *raycaster)
{
	raycaster->backX = raycaster->mapX / 2;
	raycaster->backY = raycaster->mapY / 2;
	raycaster->backS = raycaster->side;
}

static	void	calculate_next_increment(t_raycaster_data *raycaster)
{
	if (raycaster->sideDistX < raycaster->sideDistY)
	{
		raycaster->sideDistX += raycaster->deltadistX;
		raycaster->mapX += raycaster->step_x;
		raycaster->side = FALSE;
	}
	else
	{
		raycaster->sideDistY += raycaster->deltadistY;
		raycaster->mapY += raycaster->step_y;
		raycaster->side = TRUE;
	}
}

static	double	calculate_door_intersection_ratio(t_raycaster_data *raycaster)
{
	double	intersection;

	intersection = 1;
	if (raycaster->side)
	{
		if (raycaster->rayY > 0)
			raycaster->delta = raycaster->mapY - raycaster->player_y;
		else
			raycaster->delta = raycaster->mapY - raycaster->player_y + 1;
		intersection = (raycaster->player_x + (raycaster->delta)
				/ (tan(raycaster->angle))) / 2;
	}
	if (!raycaster->side)
	{
		if (raycaster->rayX > 0)
			raycaster->delta = raycaster->mapX - raycaster->player_x;
		else
			raycaster->delta = raycaster->mapX - raycaster->player_x + 1;
		intersection = (raycaster->player_y + (raycaster->delta)
				* (tan(raycaster->angle))) / 2;
	}
	intersection = intersection - (int) intersection;
	return (intersection);
}

static	t_boolean	inside_wall(t_cub3d *cub3d, t_raycaster_data *raycaster)
{
	float	door_open_ratio;

	if (cub3d->mini_map[raycaster->backY][raycaster->backX] == 'D'
		&& (raycaster->backS == raycaster->side || raycaster->pass_door))
	{
		if (is_open_door(cub3d->door, raycaster->mapX / 2,
				raycaster->mapY / 2, &door_open_ratio) == FALSE)
			raycaster->hit = TRUE;
		else if (calculate_door_intersection_ratio(raycaster) > door_open_ratio)
			raycaster->hit = TRUE;
		raycaster->door = TRUE;
	}
	if (cub3d->mini_map[raycaster->backY][raycaster->backX] == 'D'
		&& raycaster->backS != raycaster->side)
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
	rc->angle = atan(rc->rayY / rc->rayX);
	while (!rc->hit)
	{
		rc->door = FALSE;
		rc->door_side = FALSE;
		if (cub3d->mini_map[rc->mapY / 2][rc->mapX / 2] == 'D')
			rc->door_side = TRUE;
		calculate_next_increment(rc);
		if (rc->mapX <= 0 || rc->mapY <= 0
			|| rc->mapY / 2 > (int) rc->rows_count
			|| rc->mapX / 2 > (int) cub3d->mini_map_line_len[rc->mapY / 2]
			|| cub3d->mini_map[rc->mapY / 2][rc->mapX / 2] == 'D')
			inside_wall(cub3d, rc);
		if (rc->mapX <= 0 || rc->mapY <= 0
			|| rc->mapY / 2 > (int) rc->rows_count
			|| rc->mapX / 2 > (int) cub3d->mini_map_line_len[rc->mapY / 2]
			|| cub3d->mini_map[rc->mapY / 2][rc->mapX / 2] == '1')
			rc->hit = TRUE;
		make_dda_backup(rc);
	}
}
