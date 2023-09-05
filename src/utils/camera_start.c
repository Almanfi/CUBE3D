/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:24:29 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/05 16:02:49 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir_and_fov(t_cub3d *cub3d, double dir[2], double fov[2])
{
	cub3d->raycaster.direction_x = dir[0];
	cub3d->raycaster.direction_y = dir[1];
	cub3d->raycaster.camera_x = fov[0];
	cub3d->raycaster.camera_y = fov[1];
}

static double	*set_vector(double vec[2], double x, double y)
{
	vec[0] = x;
	vec[1] = y;
	return (vec);
}

void	set_camera_cord(t_cub3d *cub3d, char c)
{
	double	fov[2];
	double	dir[2];

	if (c == 'W')
		set_dir_and_fov(cub3d, set_vector(dir, -1.0, 0.0), set_vector(fov, 0.0,
				-0.66));
	else if (c == 'S')
		set_dir_and_fov(cub3d, set_vector(dir, 0.0, 1.0), set_vector(fov, -0.66,
				0));
	else if (c == 'E')
		set_dir_and_fov(cub3d, set_vector(dir, 1.0, 0.0), set_vector(fov, 0.0,
				0.66));
	else if (c == 'N')
		set_dir_and_fov(cub3d, set_vector(dir, 0.0, -1.0), set_vector(fov, 0.66,
				0.0));
}
