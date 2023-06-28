/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:31:38 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/28 22:17:19 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*texture_side(char **line, t_cub3d *cub3d)
{
	if (ft_is_space(*(*line + 2)))
	{
		if (!ft_strncmp(*line, "NO", 3) && !cub3d->texture.north)
			return &cub3d->texture.north;
		else if (!ft_strncmp(*line, "EA", 3) && !cub3d->texture.east)
			return &cub3d->texture.east;
		else if (!ft_strncmp(*line, "SO", 3) && !cub3d->texture.south)
			return &cub3d->texture.south;
		else if (!ft_strncmp(*line, "WE", 3) && !cub3d->texture.west)
			return &cub3d->texture.west;
		*line = *line + 2;
	}
	return NULL;
}

static	void	open_texture_file(char **line, int *fd)
{
	size_t	i;

	*line = skip_space(*line);
	if (!*line)
		exit_cub3d(-1,"empty texture line");
	i = 0;
	while ((*line)[i] && !ft_is_space((*line)[i]))
		i++;
	*fd = open(*line, O_RDONLY);
	if (*fd == -1)
		exit_cub3d(-1, "couldn't open a texture file");
}

static t_boolean	filled_everything(t_cub3d *cub3d)
{
	if (cub3d->texture.north && cub3d->texture.east
		&& cub3d->texture.south && cub3d->texture.west
		&& cub3d->texture.floor_is_set)
		return TRUE;
	return FALSE;
}

void    parse_textures(t_cub3d *cub3d)
{
	char	*line;
	int		*texture_to_fill;

	while (cub3d->map_content)
	{
		texture_to_fill = NULL;
		line = skip_space(*cub3d->map_content);
		if (*line)
		{
			texture_to_fill = texture_side(line, cub3d);
			if (!texture_to_fill)
				floor_color(line, cub3d);
			else
				open_texture_file(&line, texture_to_fill);
		}
		ft_free_node(GNL_SCOPE, *cub3d->map_content);
		cub3d->map_content++;
		if (filled_everything(cub3d))
			break;
	}
}