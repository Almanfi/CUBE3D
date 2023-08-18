/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 04:05:05 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/18 04:25:37 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static  void    draw_floor(t_cub3d *cub3d, int row)
{
    size_t  columns;
    // t_raycaster_data *raycaster;
    int              floor_color;
    int              ceiling_color;
    // int              cells[2];

    columns = 0;
    // raycaster = &cub3d->raycaster;
    floor_color = ((cub3d->texture.floor.r << 16) + (cub3d->texture.floor.g << 8) + cub3d->texture.floor.b); 
    ceiling_color = 30850;
    while (columns < WINDOW_WIDTH)
    {   
        // raycaster->floor_cords[X] += raycaster->floor_step[X];
        // raycaster->floor_cords[Y] += raycaster->floor_step[Y];
        cub3d_pixel_put(cub3d, columns, row, floor_color);
        cub3d_pixel_put(cub3d, columns, WINDOW_HEIGHT - row - 1, ceiling_color);
        columns++;
    }
}

void    cast_floor(t_cub3d *cub3d)
{
    size_t  rows;
    // t_raycaster_data *raycaster;

    rows = 0;
    // raycaster = &cub3d->raycaster;
    while (rows < WINDOW_HEIGHT)
    {
        // raycaster->leftest_ray[X] = raycaster->direction_x - raycaster->camera_x;
        // raycaster->leftest_ray[Y] = raycaster->direction_y - raycaster->camera_y;
        // raycaster->rightest_ray[X] = raycaster->direction_x + raycaster->camera_x;
        // raycaster->rightest_ray[Y] = raycaster->direction_y + raycaster->camera_y;
        // raycaster->current_y = rows - WINDOW_HEIGHT / 2;
        // raycaster->vertical_pos = (double) 0.5 * WINDOW_HEIGHT;
        // raycaster->row_distance = raycaster->vertical_pos / raycaster->current_y;
        // raycaster->floor_step[X] = raycaster->row_distance * ((raycaster->rightest_ray[X] - raycaster->leftest_ray[X]) / WINDOW_WIDTH);
        // raycaster->floor_step[Y] = raycaster->row_distance *((raycaster->rightest_ray[Y] - raycaster->leftest_ray[Y]) / WINDOW_WIDTH);
        // raycaster->floor_cords[X] = raycaster->player_x + raycaster->row_distance * raycaster->leftest_ray[X];
        // raycaster->floor_cords[Y] = raycaster->player_y + raycaster->row_distance * raycaster->leftest_ray[Y];
        draw_floor(cub3d, rows);
        rows++;
    }
}
