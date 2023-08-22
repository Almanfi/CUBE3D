/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:55:41 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/22 10:06:21 by bamrouch         ###   ########.fr       */
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
    void    *img;
    void    **temp;

    img = mlx_xpm_file_to_image(cub3d->mlx, "./barrel.xpm",&(cub3d->img_width), &(cub3d->img_height));
    if (!img)
        exit_cub3d(-1, "couldn't open sprite file");
    temp = cub3d->imgs;
	cub3d->imgs = add_element_to_array(temp, &img, sizeof(void *));
	if (!cub3d->imgs)
		exit_cub3d(ENOMEM, "couldn't save sprites pointers");
	ft_free_node(1, temp);   
    store_texture(cub3d, SPRITE, img); 
}

t_cub3d *get_cub3d(t_cub3d *cub3d)
{
    static  t_cub3d *p_cub3d;

    if (cub3d)
        p_cub3d = cub3d;
    return p_cub3d;
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    t_cub3d cub3d;

    ft_bzero(&cub3d, sizeof(t_cub3d));
    get_cub3d(&cub3d);
    cub3d_mlx_init(&cub3d);
    cub3d_parser(argc, argv, &cub3d);
    read_sprites(&cub3d);
    draw_cub3d(&cub3d);
    mlx_loop(cub3d.mlx);
}
