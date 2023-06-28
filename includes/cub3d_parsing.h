/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:46:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/28 20:39:59 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
#define CUB3D_PARSING_H
#include "cub3d.h"


// int_parser.c
t_boolean	ft_str_is_integer(const char *str, int *res);

// floor_parser.c
void        floor_parser(char *line, t_cub3d *cub3d);


void    exit_cub3d(int  err_code, char *message);

#endif