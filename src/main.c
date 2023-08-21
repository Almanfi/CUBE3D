/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:55:41 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/21 16:22:21 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    set_starting_position(t_cub3d *cub3d)
{
	cub3d->raycaster.direction_x = CAMERA_DIR_X;
	cub3d->raycaster.direction_y = CAMERA_DIR_Y;
	cub3d->raycaster.camera_x = CAMERA_FOV_X;
	cub3d->raycaster.camera_y = CAMERA_FOV_Y;
}

void    read_sprites(t_cub3d *cub3d)
{
    cub3d->img = mlx_xpm_file_to_image(cub3d->mlx, "./barrel.xpm",&(cub3d->img_width), &(cub3d->img_height));
    if (!cub3d->img)
        exit_cub3d(-1, "couldn't open sprite file");
    store_texture(cub3d, SPRITE); 
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    t_cub3d cub3d;

    ft_bzero(&cub3d, sizeof(t_cub3d));
    cub3d_mlx_init(&cub3d);
    cub3d_parser(argc, argv, &cub3d);
    set_starting_position(&cub3d);
    read_sprites(&cub3d);
    draw_cub3d(&cub3d);
    mlx_loop(cub3d.mlx);
}
