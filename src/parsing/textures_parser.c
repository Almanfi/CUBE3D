/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:31:38 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/02 22:22:54 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*texture_side(char **line, t_cub3d *cub3d)
{
	int	*texture;
	
	texture = NULL;
	if (ft_is_space(*(*line + 2)))
	{
		if (!ft_strncmp(*line, "NO", 2) && !cub3d->texture.north)
			texture = &cub3d->texture.north;
		else if (!ft_strncmp(*line, "EA", 2) && !cub3d->texture.east)
			texture = &cub3d->texture.east;
		else if (!ft_strncmp(*line, "SO", 2) && !cub3d->texture.south)
			texture = &cub3d->texture.south;
		else if (!ft_strncmp(*line, "WE", 2) && !cub3d->texture.west)
			texture = &cub3d->texture.west;
		if (texture)
			*line = *line + 2;
	}
	return texture;
}

static	void	open_texture_file(char **line, int *fd)
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

	while (*cub3d->map_content && !filled_everything(cub3d))
	{
		line = skip_space(*cub3d->map_content);
		if (*line)
		{
			texture_to_fill = NULL;
			texture_to_fill = texture_side(&line, cub3d);
			if (!texture_to_fill)
				floor_parser(line, cub3d);
			else
				open_texture_file(&line, texture_to_fill);
		}
		ft_free_node(GNL_SCOPE, *cub3d->map_content);
		cub3d->map_content++;
	}
	if (!filled_everything(cub3d))
		exit_cub3d(-1, "not all textures are set");
}