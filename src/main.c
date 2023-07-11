/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:55:41 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/11 10:17:47 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    set_starting_position(t_cub3d *cub3d)
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
	cub3d->raycaster.player_x = j + 0.5;
	cub3d->raycaster.player_y = i + 0.5;
	cub3d->raycaster.direction_x = 1;
	cub3d->raycaster.direction_y = 0;
	cub3d->raycaster.camera_x = 0;
	cub3d->raycaster.camera_y = 0.66;
}

static void	generate_random_texture(t_cub3d *cub3d)
{
	int	x;
	int	y;
	int	xor_color;
	int	y_color;
	int	xy_color;

	x = 0;
	while (x < TEX_DIMENSIONS)
	{
		y = 0;
		while (y < TEX_DIMENSIONS)
		{
			xor_color = (x * 256 / TEX_DIMENSIONS) ^ (y * 256 / TEX_DIMENSIONS);
			y_color = y * 256 / TEX_DIMENSIONS;
   			xy_color = y * 128 / TEX_DIMENSIONS + x * 128 / TEX_DIMENSIONS;
			cub3d->texture.r_textures[0][TEX_DIMENSIONS * y + x] = 65536 * 254 * (x != y && x != TEX_DIMENSIONS - y);
			cub3d->texture.r_textures[1][TEX_DIMENSIONS * y + x] = xy_color + 256 * xy_color + 65536 * xy_color;
			cub3d->texture.r_textures[2][TEX_DIMENSIONS * y + x] = 256 * xy_color + 65536 * xy_color;
			cub3d->texture.r_textures[3][TEX_DIMENSIONS * y + x] = xor_color + 256 * xor_color + 65536 * xor_color;
			cub3d->texture.r_textures[4][TEX_DIMENSIONS * y + x] = 256 * xor_color;
			cub3d->texture.r_textures[5][TEX_DIMENSIONS * y + x] = 65536 * 192 * (x % 16 && y % 16);
			cub3d->texture.r_textures[6][TEX_DIMENSIONS * y + x] = 65536 * y_color;
			cub3d->texture.r_textures[7][TEX_DIMENSIONS * y + x] = 128 + 256 * 128 + 65536 * 128;
			y++;
		}
		x++;
	}
}

// static	void	read_textures(t_cub3d *cub3d)
// {
	

// }

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    t_cub3d cub3d;

    ft_bzero(&cub3d, sizeof(t_cub3d));
    cub3d_parser(argc, argv, &cub3d);
    cub3d_mlx_init(&cub3d);
	printf("the row count is : %zu\n", cub3d.raycaster.rows_count);
	printf("the columns count is : %zu\n", cub3d.raycaster.columns_count);
    set_starting_position(&cub3d);
	generate_random_texture(&cub3d);
    draw_cub3d(&cub3d);
    mlx_loop(cub3d.mlx);
}
