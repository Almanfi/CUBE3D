/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:35:04 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/07 14:23:13 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    cub3d_pixel_put(t_cub3d *cub3d, int x, int y, unsigned int color)
{
  unsigned int    *addr;

  addr = (unsigned int *) cub3d->frame.addr;
  if (x >= 0 && x < WINDOW_WIDTH && y >= 0
    && y < WINDOW_HEIGHT)
		addr[x + (y * WINDOW_WIDTH)] = (unsigned int)color;
}

