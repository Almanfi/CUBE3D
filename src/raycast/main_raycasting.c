/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:31:04 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/07 19:35:10 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub3d *cub3d, int x, int y, int dimensions)
{
	int	temp_y;
	int temp_x;

	temp_y = y;
	temp_x = x;
	while (x < temp_x + dimensions)
	{
		y = temp_y;
		while (y < temp_y + dimensions)
		{
			cub3d_pixel_put(cub3d, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}


void    draw_player(t_cub3d *cub3d)
{
    size_t	i;
	size_t	j;
	char	**map;

	i = 0;
	map = cub3d->mini_map;
	while (map[i])
	{
		j = 0;
		while(map[i][j] && !is_start_pos(map[i][j]))
			j++;
		if (is_start_pos(map[i][j]))
			break;
		i++;
	}
	j = (CUBE_DIMENSIONS * j + CUBE_DIMENSIONS / 2) + cub3d->p_move.x;
	i = (CUBE_DIMENSIONS * i + CUBE_DIMENSIONS / 2) + cub3d->p_move.y;
	
	draw_square(cub3d, j, i, 10);
}

void	draw_map(t_cub3d *cub3d)
{
	size_t	i;
	size_t	j;
	char	**map;

	i = 0;
	map = cub3d->mini_map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(cub3d, j * CUBE_DIMENSIONS, i * CUBE_DIMENSIONS, CUBE_DIMENSIONS);
			j++;
		}
		i++;
	}
}

void	draw_cub3d(t_cub3d *cub3d)
{
	cub3d_window_init(cub3d);
	cub3d_frame_init(cub3d);
	draw_player(cub3d);
	draw_map(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->frame.img, 0, 0);

}

