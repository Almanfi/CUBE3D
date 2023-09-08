/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:46:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/08 20:30:58 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H
# include "cub3d.h"

// int_parser.c
t_boolean	ft_str_is_integer(const char *str, int *res);

// floor_parser.c
void	floor_parser(char *line, t_cub3d *cub3d,
				t_tx_type *texture);

// textures_parser.c
void		parse_textures(t_cub3d *cub3d);
void		store_texture(t_cub3d *cub3d, t_tx_type tx_side, void *img);
void		read_texture_file(t_cub3d *cub3d, t_tx_type tx_side, char *line);

// map_parser.c
t_boolean	is_start_pos(char c);
void		map_parser(t_cub3d *cub3d);

// main_parser.c
void		cub3d_parser(int argc, char *argv[], t_cub3d *cub3d);

#endif