/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:31:38 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/18 20:46:15 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tx_type	texture_side(char **line, t_cub3d *cub3d)
{
	t_tx_type	texture;
	
	texture = FLOOR;
	if (ft_is_space(*(*line + 2)))
	{
		if (!ft_strncmp(*line, "NO", 2) && !cub3d->texture.tx_set[NORTH] && ++(cub3d->texture.tx_set[NORTH]))
			texture = NORTH;
		else if (!ft_strncmp(*line, "EA", 2) && !cub3d->texture.tx_set[EAST] && ++(cub3d->texture.tx_set[EAST]))
			texture = EAST;
		else if (!ft_strncmp(*line, "SO", 2) && !cub3d->texture.tx_set[SOUTH] && ++(cub3d->texture.tx_set[SOUTH]))
			texture = SOUTH;
		else if (!ft_strncmp(*line, "WE", 2) && !cub3d->texture.tx_set[WEST] && ++(cub3d->texture.tx_set[WEST]))
			texture = WEST;
		if (texture != NOT_DEFINED)
			*line = *line + 2;
	}
	return (texture);
}

void	generate_random_texture(t_cub3d *cub3d)
{
	int	x;
	int	y;
	int	xor_color;
	int	y_color;
	int	xy_color;
	t_frame_data texture_data;

	texture_data.addr = mlx_get_data_addr(cub3d->img, &texture_data.bits_per_pixel, &texture_data.line_length, &texture_data.endian);
	x = 0;
	while (x < TEX_DIMENSIONS)
	{
		y = 0;
		while (y < TEX_DIMENSIONS)
		{
			xor_color = (x * 256 / TEX_DIMENSIONS) ^ (y * 256 / TEX_DIMENSIONS);
			y_color = y * 256 / TEX_DIMENSIONS;
   			xy_color = y * 128 / TEX_DIMENSIONS + x * 128 / TEX_DIMENSIONS;
			cub3d->texture.tx[0][TEX_DIMENSIONS * y + x] = 65536 * 254 * (x != y && x != TEX_DIMENSIONS - y);
			cub3d->texture.tx[1][TEX_DIMENSIONS * y + x] = ((int *)texture_data.addr)[(texture_data.line_length / 4) * y + x];
			cub3d->texture.tx[2][TEX_DIMENSIONS * y + x] = 256 * xy_color + 65536 * xy_color;
			cub3d->texture.tx[3][TEX_DIMENSIONS * y + x] = xor_color + 256 * xor_color + 65536 * xor_color;
			cub3d->texture.tx[4][TEX_DIMENSIONS * y + x] = 256 * xor_color;
			cub3d->texture.tx[5][TEX_DIMENSIONS * y + x] = 65536 * 192 * (x % 16 && y % 16);
			cub3d->texture.tx[6][TEX_DIMENSIONS * y + x] = 65536 * y_color;
			cub3d->texture.tx[7][TEX_DIMENSIONS * y + x] = 128 + 256 * 128 + 65536 * 128;
			y++;
		}
		x++;
	}
}

static void store_texture(t_cub3d *cub3d, t_tx_type tx_side)
{
	int	x;
	int	y;
	t_frame_data texture_data;

	texture_data.addr = mlx_get_data_addr(cub3d->img, &texture_data.bits_per_pixel, &texture_data.line_length, &texture_data.endian);
	x = 0;
	while (x < TEX_DIMENSIONS)
	{
		y = 0;
		while (y < TEX_DIMENSIONS)
		{
			cub3d->texture.tx[tx_side][TEX_DIMENSIONS * y + x] = ((int *)texture_data.addr)[(texture_data.line_length / 4) * y + x];
			y++;
		}
		x++;
	}

}

static	void	open_texture_file(char **line, t_cub3d *cub3d, t_tx_type side)
{
	size_t	i;
	size_t	j;

	*line = skip_space(*line);
	if (!*line)
		exit_cub3d(-1,"empty texture line");
	i = 0;
	while ((*line)[i] && !ft_is_space((*line)[i]))
		i++;
	
	if ((*line)[i])
	{
		(*line)[i] = 0;
		j = i + 1;
		while ((*line)[j] && ft_is_space((*line)[j]))
			j++;
		if ((*line)[j])
			exit_cub3d(-1, "unrespected texture format");
	}
	cub3d->img = mlx_xpm_file_to_image(cub3d->mlx, *line, &(cub3d->img_width), &(cub3d->img_height));
	if (!cub3d->img)
		exit_cub3d(-1, "couldn't open a texture file");
	store_texture(cub3d, side);
}

static t_boolean	filled_everything(t_cub3d *cub3d)
{
	if (cub3d->texture.tx_set[NORTH] && cub3d->texture.tx_set[SOUTH]
		&& cub3d->texture.tx_set[EAST] && cub3d->texture.tx_set[WEST]
		&& cub3d->texture.floor_is_set && cub3d->texture.ceiling_is_set)
		return TRUE;
	return FALSE;
}

void    parse_textures(t_cub3d *cub3d)
{
	char		*line;
	t_tx_type	texture_to_fill;

	while (*cub3d->map_content && !filled_everything(cub3d))
	{
		line = skip_space(*cub3d->map_content);
		if (*line)
		{
			texture_to_fill = NOT_DEFINED;
			texture_to_fill = texture_side(&line, cub3d);
			if (texture_to_fill == FLOOR)
				floor_parser(line, cub3d);
			else
				open_texture_file(&line, cub3d, texture_to_fill);
		}
		ft_free_node(GNL_SCOPE, *cub3d->map_content);
		cub3d->map_content++;
		cub3d->content_len++;
	}
	if (!filled_everything(cub3d))
		exit_cub3d(-1, "not all textures are set");
}