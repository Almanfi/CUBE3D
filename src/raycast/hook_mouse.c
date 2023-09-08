/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:59:16 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/08 13:09:57 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_rotation(int x, int y, t_cub3d *cub3d)
{
	static int	i;

	i++;
	(void) y;
	if (x > WINDOW_WIDTH / 2 + 2)
		cub3d->rotation_dir = 1;
	else if (x < WINDOW_WIDTH / 2 - 2)
		cub3d->rotation_dir = -1;
	if (i % 2)
		mlx_mouse_move(cub3d->mlx,
			cub3d->window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_mouse_hide(cub3d->mlx, cub3d->window);
	return (0);
}
