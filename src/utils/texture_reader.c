/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:47:32 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/04 19:48:23 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_texture(t_cub3d *cub3d, t_tx_type tx_side, void *img)
{
	int				x;
	int				y;
	t_frame_data	texture_data;

	texture_data.addr = mlx_get_data_addr(img, &texture_data.bits_per_pixel,
			&texture_data.line_length, &texture_data.endian);
	x = 0;
	while (x < TEX_DIMENSIONS)
	{
		y = 0;
		while (y < TEX_DIMENSIONS)
		{
			cub3d->texture.tx[tx_side][TEX_DIMENSIONS * y
				+ x] = ((int *)texture_data.addr)[(texture_data.line_length / 4)
				* y + x];
			y++;
		}
		x++;
	}
}

void	read_texture_file(t_cub3d *cub3d, t_tx_type tx_side, char *line)
{
	void	*img;

	img = mlx_xpm_file_to_image(cub3d->mlx, line, &(cub3d->img_width),
			&(cub3d->img_height));
	if (!img)
		exit_cub3d(-1, "couldn't open a texture file");
	cub3d->imgs = add_element_to_array(cub3d->imgs, &img, sizeof(void *));
	if (!cub3d->imgs)
		exit_cub3d(ENOMEM, "couldn't save texture pointers");
	store_texture(cub3d, tx_side, img);
}
