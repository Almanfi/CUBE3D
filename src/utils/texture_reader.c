/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:47:32 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/08 19:54:37 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_texture(t_cub3d *cub3d, t_tx_type tx_side, void *img)
{
	double			step_x;
	double			step_y;
	int				x;
	int				y;
	t_frame_data	texture_data;

	texture_data.addr = mlx_get_data_addr(img, &texture_data.bits_per_pixel,
			&texture_data.line_length, &texture_data.endian);
	step_x = (double )TEX_DIMENSIONS / cub3d->img_width;
	step_y = (double )TEX_DIMENSIONS / cub3d->img_height;
	x = 0;
	while (x < (int )(cub3d->img_width * step_x))
	{
		y = 0;
		while (y < (int )(cub3d->img_height * step_y))
		{
			cub3d->texture.tx[tx_side][TEX_DIMENSIONS * y
				+ x] = ((int *)texture_data.addr)[(texture_data.line_length / 4)
				* (int )(y / step_y) + (int )(x / step_x)];
			y++;
		}
		x++;
	}
}

void	read_texture_file(t_cub3d *cub3d, t_tx_type tx_side, char *line)
{
	void	*img;
	void	**temp;

	printf("|%s|\n", line);
	img = mlx_xpm_file_to_image(cub3d->mlx, line, &(cub3d->img_width),
			&(cub3d->img_height));
	if (!img)
		exit_cub3d(-1, "couldn't open a texture file");
	temp = cub3d->imgs;
	cub3d->imgs = add_element_to_array(cub3d->imgs, &img, sizeof(void *));
	if (!cub3d->imgs)
		exit_cub3d(ENOMEM, "couldn't save texture pointers");
	ft_free_node(1, temp);
	store_texture(cub3d, tx_side, img);
}
