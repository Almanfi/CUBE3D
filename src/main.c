/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:55:41 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/30 23:49:51 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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

void    read_animated_sprites(t_cub3d *cub3d)
{
    void    *img;
    void    **temp;
    char    path[] = "fire_head/1.xpm";
    int     i;

    i = 0;
    while (i < 5)
    {
        path[10] = '1' + i;
        img = mlx_xpm_file_to_image(cub3d->mlx, path, &(cub3d->img_width), &(cub3d->img_height));
        if (!img)
            exit_cub3d(-1, "couldn't open sprite file");
        temp = cub3d->imgs;
        cub3d->imgs = add_element_to_array(temp, &img, sizeof(void *));
        if (!cub3d->imgs)
            exit_cub3d(ENOMEM, "couldn't save sprites pointers");
        ft_free_node(1, temp);
        store_texture(cub3d, FIREHEAD1 + i, img);
        i++;
    }
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
    read_animated_sprites(&cub3d);
    cub3d.door_step = 0.1;
    draw_cub3d(&cub3d);
    mlx_loop(cub3d.mlx);
}
