/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:37:34 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/27 19:28:57 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

#include "ft_garbage_collector.h"
#include "cub3d_parsing.h"
#include "errno.h"
#include <mlx.h>

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}   t_rgb;


typedef struct s_textures
{
    int north;
    int east;
    int south;
    int west;
    int floor;
}   t_textures;

typedef struct s_cub3d
{
    char        **map_content;
    t_textures  texture;
}   t_cub3d;


// utils
//skip_space.c
t_boolean	skip_space(char *str);

// array_utils.c
void	*add_element_to_array(void *old_array, void *new_elem, size_t data_size);
void	*add_arr_to_array(void *dest_arr, void *src_arr, size_t data_size);


#endif