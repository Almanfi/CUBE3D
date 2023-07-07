/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:28:19 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/07 18:32:43 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    cub3d_window_init(t_cub3d *cub3d)
{
    if (!cub3d->window)
    {
        cub3d->window = mlx_new_window(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
        if (!cub3d->window)
            exit_cub3d(-1, "mlx new window didnt work");
        cub3d_hooks(cub3d);
    }
    else
        mlx_clear_window(cub3d->mlx, cub3d->window);
}

void    cub3d_frame_init(t_cub3d *cub3d)
{
    if (!cub3d->frame.img)
    {
        cub3d->frame.img = mlx_new_image(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
        if (!cub3d->frame.img)
            exit_cub3d(-1, "mlx new image didnt work");
        cub3d->frame.addr = mlx_get_data_addr(cub3d->frame.img, 
            &cub3d->frame.bits_per_pixel, &cub3d->frame.line_length, &cub3d->frame.endian);
        if (!cub3d->frame.addr)
            exit_cub3d(-1, "mlx get data addr didnt work");   
    }
    else
    {
        mlx_destroy_image(cub3d->mlx, cub3d->frame.img);
        cub3d->frame.img = NULL;
        cub3d->frame.addr = NULL;
        cub3d_frame_init(cub3d);
    }
}

void    cub3d_mlx_init(t_cub3d *cub3d)
{
    cub3d->mlx = mlx_init();
    if (!cub3d->mlx)
        exit_cub3d(-1, "mlx init didn't work");
}
