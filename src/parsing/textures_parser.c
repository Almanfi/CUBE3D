/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:31:38 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/08 16:40:41 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tx_type	texture_side(char **line, t_cub3d *cub3d)
{
	t_tx_type	texture;

	texture = NOT_DEFINED;
	if (ft_is_space(*(*line + 2)))
	{
		if (!ft_strncmp(*line, "NO", 2) && !cub3d->texture.tx_set[NORTH]
			&& ++(cub3d->texture.tx_set[NORTH]))
			texture = NORTH;
		else if (!ft_strncmp(*line, "EA", 2) && !cub3d->texture.tx_set[EAST]
			&& ++(cub3d->texture.tx_set[EAST]))
			texture = EAST;
		else if (!ft_strncmp(*line, "SO", 2) && !cub3d->texture.tx_set[SOUTH]
			&& ++(cub3d->texture.tx_set[SOUTH]))
			texture = SOUTH;
		else if (!ft_strncmp(*line, "WE", 2) && !cub3d->texture.tx_set[WEST]
			&& ++(cub3d->texture.tx_set[WEST]))
			texture = WEST;
		else if (!ft_strncmp(*line, "DO", 2) && !cub3d->texture.tx_set[DOOR]
			&& ++(cub3d->texture.tx_set[DOOR]))
			texture = DOOR;
		if (texture != NOT_DEFINED)
			*line = *line + 2;
	}
	return (texture);
}

static void	open_texture_file(char **line, t_cub3d *cub3d, t_tx_type side)
{
	size_t	i;
	size_t	j;

	*line = skip_space(*line);
	if (!*line)
		exit_cub3d(-1, "empty texture line");
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
	read_texture_file(cub3d, side, *line);
}

static t_boolean	filled_everything(t_cub3d *cub3d)
{
	if (cub3d->texture.tx_set[NORTH] && cub3d->texture.tx_set[SOUTH]
		&& cub3d->texture.tx_set[EAST] && cub3d->texture.tx_set[WEST]
		&& cub3d->texture.tx_set[DOOR] && cub3d->texture.floor_is_set
		&& cub3d->texture.ceiling_is_set)
		return (TRUE);
	return (FALSE);
}

void	parse_textures(t_cub3d *cub3d)
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
			if (texture_to_fill == NOT_DEFINED)
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
