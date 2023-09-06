/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:59:16 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/06 18:02:12 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_rotation(int x, int y, t_cub3d *cub3d)
{
	printf("x = %d\n", x);
	if (cub3d->mouse_x > x)
		cub3d->rotation_dir = -1;
	else if (cub3d->mouse_x < x)
		cub3d->rotation_dir = 1;
	if (x == 0 && cub3d->mouse_x == 0)
		cub3d->rotation_dir = -1;
	else if (x == WINDOW_WIDTH -1 && cub3d->mouse_x == WINDOW_WIDTH -1)
		cub3d->rotation_dir = 1;
	cub3d->mouse_x = x;
	(void) y;
	return (0);
}
