/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:36:11 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/30 21:30:59 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// void    move_player(t_cub3d *cub3d)
// {
//     double x;
//     double y;
//     t_raycaster_data *raycaster;

//     raycaster = &cub3d->raycaster;
//     y = raycaster->player_x + cub3d->move_vertical * raycaster->direction_x * (MOVE_SPEED + HB_RADIUS)
//         + 0.7 * cub3d->move_horizontal * raycaster->camera_x * (MOVE_SPEED + HB_RADIUS);
//     x = raycaster->player_y;
//     if (cast_rays_for_collision(cub3d, x, y) == FALSE)
//         raycaster->player_x += cub3d->move_vertical * raycaster->direction_x * MOVE_SPEED
//             + 0.7 * cub3d->move_horizontal * raycaster->camera_x * (MOVE_SPEED + HB_RADIUS);
//     y = raycaster->player_x;
//     x = raycaster->player_y + cub3d->move_vertical * raycaster->direction_y * (MOVE_SPEED + HB_RADIUS)
//         + 0.7 * cub3d->move_horizontal * raycaster->camera_y * (MOVE_SPEED + HB_RADIUS);
//      if (cast_rays_for_collision(cub3d, x, y) == FALSE)
//         raycaster->player_y += cub3d->move_vertical * raycaster->direction_y * MOVE_SPEED
//         + 0.7 * cub3d->move_horizontal * raycaster->camera_y * (MOVE_SPEED + HB_RADIUS);
// }

static  t_boolean check_sprite_collision(t_cub3d *cub3d, double x, double y)
	{
	size_t i;

	i = 0;
	while (i < cub3d->sprite_count)
	{
		if (x >= cub3d->sprites[i]->x - 0.5 && x <= cub3d->sprites[i]->x + 0.5
			&& y >= cub3d->sprites[i]->y - 0.5 && y <= cub3d->sprites[i]->y + 0.5)
			return (TRUE);
		i++;
	}

	return (FALSE);
}

void    move_player(t_cub3d *cub3d)
{
    double				x;
    double				y;
    t_raycaster_data	*raycaster;
    float				move_speed;

	move_speed = ((double) MOVE_SPEED * WINDOW_HEIGHT) / 500;
	raycaster = &cub3d->raycaster;
	y = raycaster->player_x + cub3d->move_vertical * raycaster->direction_x * move_speed
		+ 0.7 * cub3d->move_horizontal * raycaster->camera_x * move_speed;
	x = raycaster->player_y;
	if (cub3d->mini_map[(int) x][(int) y] == '0' && check_sprite_collision(cub3d, y, x) == FALSE)
		raycaster->player_x += cub3d->move_vertical * raycaster->direction_x * move_speed
			+ 0.7 * cub3d->move_horizontal * raycaster->camera_x * move_speed;
	y = raycaster->player_x;
	x = raycaster->player_y + cub3d->move_vertical * raycaster->direction_y * move_speed
		+ 0.7 * cub3d->move_horizontal * raycaster->camera_y * move_speed;
	if (cub3d->mini_map[(int) x][(int) y] == '0' && check_sprite_collision(cub3d, y, x) == FALSE)
		raycaster->player_y += cub3d->move_vertical * raycaster->direction_y * move_speed
		+ 0.7 * cub3d->move_horizontal * raycaster->camera_y * move_speed;
}

void    rotate_player(t_cub3d *cub3d)
{
	t_raycaster_data	*raycaster;
	double				old_directionX;
	double				old_cameraX;
	double				rot_speed;

	raycaster = &cub3d->raycaster;
	rot_speed = cub3d->rotation_dir * degree_to_rad(((double) ROT_SPEED * WINDOW_WIDTH) / 500);
	old_directionX = raycaster->direction_x;
	old_cameraX = raycaster->camera_x;
	raycaster->direction_x = old_directionX * cos(rot_speed) - raycaster->direction_y * sin(rot_speed);
	raycaster->direction_y = old_directionX * sin(rot_speed) + raycaster->direction_y * cos(rot_speed);
	raycaster->camera_x = old_cameraX * cos(rot_speed) - raycaster->camera_y * sin(rot_speed);
	raycaster->camera_y = old_cameraX * sin(rot_speed) + raycaster->camera_y * cos(rot_speed);
}

