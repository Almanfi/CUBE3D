/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:36:11 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/11 08:36:55 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void    move_backwards(t_cub3d *cub3d)
{
    int x;
    int y;
    t_raycaster_data *raycaster;

    raycaster = &cub3d->raycaster;
    x = raycaster->player_x - raycaster->direction_x * MOVE_SPEED;
    y = raycaster->player_y;
    if (cub3d->mini_map[x][y] == '0')
        raycaster->player_x -= raycaster->direction_x * MOVE_SPEED;
    x = raycaster->player_x;
    y = raycaster->player_y - raycaster->direction_y * MOVE_SPEED;
    if (cub3d->mini_map[x][y] == '0')
        raycaster->player_y -= raycaster->direction_y * MOVE_SPEED;
}

void    move_forwards(t_cub3d *cub3d)
{
    int x;
    int y;
    t_raycaster_data *raycaster;

    raycaster = &cub3d->raycaster;
    x = raycaster->player_x + raycaster->direction_x * MOVE_SPEED;
    y = raycaster->player_y;
    if (cub3d->mini_map[x][y] == '0')
        raycaster->player_x += raycaster->direction_x * MOVE_SPEED;
    x = raycaster->player_x;
    y = raycaster->player_y + raycaster->direction_y * MOVE_SPEED;
    if (cub3d->mini_map[x][y] == '0')
        raycaster->player_y += raycaster->direction_y * MOVE_SPEED;
}

void    rotate_clockwise(t_cub3d *cub3d)
{
    double	old_directionX;
    double	old_cameraX;
    t_raycaster_data *raycaster;
    double			rot_speed;

    rot_speed = degree_to_rad(ROT_SPEED);
    raycaster = &cub3d->raycaster;
    old_directionX = raycaster->direction_x;
    old_cameraX = raycaster->camera_x;
    raycaster->direction_x = old_directionX * cos(rot_speed) - raycaster->direction_y * sin(rot_speed);
    raycaster->direction_y = old_directionX * sin(rot_speed) + raycaster->direction_y * cos(rot_speed);
    raycaster->camera_x = old_cameraX * cos(rot_speed) - raycaster->camera_y * sin(rot_speed);
    raycaster->camera_y = old_cameraX * sin(rot_speed) + raycaster->camera_y * cos(rot_speed);
}

void    rotate_reverse_clockwise(t_cub3d *cub3d)
{
    double	old_directionX;
    double	old_cameraX;
    t_raycaster_data *raycaster;
    double			rot_speed;

    rot_speed = degree_to_rad(ROT_SPEED);
    raycaster = &cub3d->raycaster;
    old_directionX = raycaster->direction_x;
    old_cameraX = raycaster->camera_x;
    raycaster->direction_x = old_directionX * cos(-rot_speed) - raycaster->direction_y * sin(-rot_speed);
    raycaster->direction_y = old_directionX * sin(-rot_speed) + raycaster->direction_y * cos(-rot_speed);
    raycaster->camera_x = old_cameraX * cos(-rot_speed) - raycaster->camera_y * sin(-rot_speed);
    raycaster->camera_y = old_cameraX * sin(-rot_speed) + raycaster->camera_y * cos(-rot_speed);
}