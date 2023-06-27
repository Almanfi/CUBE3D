/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:31:38 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/27 19:58:59 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*texture_side(char *line, t_cub3d *cub3d)
{
	if (!ft_strncmp(line, "NO ", 3) &&)
		return &cub3d->texture.north;
	else if (!ft_strncmp(line, "EA ", 3))
		return &cub3d->texture.east;
	else if (!ft_strncmp(line, "SO ", 3))
		return &cub3d->texture.south;
	else if (!ft_strncmp(line, "WE ", 3))
		return &cub3d->texture.west;
	else
		return NULL;
}

static	void	floor_color(char *line, t_cub3d *cub3d)
{
	if (!ft_strncmp(line, "F ", 2));

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
			
		}
		ft_free_node(GNL_SCOPE, *cub3d->map_content);
		cub3d->map_content++;		
	}
}