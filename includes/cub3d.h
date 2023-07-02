/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:37:34 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/02 14:33:56 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

#include "ft_garbage_collector.h"
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
    int         north;
    int         east;
    int         south;
    int         west;
    t_rgb       floor;
    t_boolean   floor_is_set;
}   t_textures;

typedef struct s_cub3d
{
    char        **map_content;
    char        **mini_map;
    t_boolean   player_set;
    t_textures  texture;
}   t_cub3d;

// exit_cub3d.c
void    exit_cub3d(int  err_code, char *message);

// utils
//skip_space.c
t_boolean	ft_is_space(char c);
char        *skip_space(char *str);
// strdup.c
char	*pro_strdup(char *str);
//substr.c
char	*pro_substr(char const *s, unsigned int start, size_t len);
// array_utils.c
void	*add_element_to_array(void *old_array, void *new_elem, size_t data_size);
void	*add_arr_to_array(void *dest_arr, void *src_arr, size_t data_size);

#include "cub3d_parsing.h"

#endif