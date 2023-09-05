/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:13:43 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/05 17:02:04 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_sprite(t_cub3d *cub3d, char **map, size_t i, size_t j)
{
	t_sprite	*new_sprite;
	void		*temp_p;

	new_sprite = ft_malloc(sizeof(t_sprite), m_info(NULL, 1, NULL, 0));
	if (!new_sprite)
		exit_cub3d(-1, "couldn't malloc a new sprite pointer");
	new_sprite->x = j + 0.5;
	new_sprite->y = i - 0.5;
	new_sprite->sprite_id = SPRITE;
	if (map[i][j] == 'D')
		new_sprite->sprite_id = DOOR;
	temp_p = cub3d->sprites;
	cub3d->sprites = add_element_to_array(temp_p, &new_sprite,
			sizeof(t_sprite *));
	ft_free_node(1, temp_p);
	cub3d->sprite_count++;
}

void	set_starting_pos(t_cub3d *cub3d, char **map, size_t i, size_t j)
{
	if (cub3d->player_set)
		exit_cub3d(-1, "unvalid map due to mutiple player positions");
	else
		cub3d->player_set = TRUE;
	set_camera_cord(cub3d, map[i][j]);
	map[i][j] = '0';
	cub3d->raycaster.player_x = j + 0.5;
	cub3d->raycaster.player_y = i - 0.5;
}

void	finalize_map(t_cub3d *cub3d, char **map, size_t i)
{
	cub3d->map_content += i;
	skip_empty_lines(cub3d);
	if (*cub3d->map_content)
		exit_cub3d(-1, "garbage value after map");
	if (!cub3d->player_set)
		exit_cub3d(-1, "starting player position is mandatory");
	cub3d->map_content = map;
	set_mini_map(cub3d, i);
}

void	map_conditions(t_cub3d *cub3d, char **map, size_t i, size_t j)
{
	if (map[i][j] == '1' || ft_is_space(map[i][j]))
		;
	else if ((map[i][j] == '0' || map[i][j] == 'D' || map[i][j] == 'I'
			|| is_start_pos(map[i][j])) && (j == 0 || open_wall(map, i, j)))
		exit_cub3d(-1, "unvalid map due to unclosed walls");
	else if (map[i][j] == 'D' && (map[i - 1][j] != '1' || map[i + 1][j] != '1')
		&& (map[i][j + 1] != '1' || map[i][j - 1] != '1'))
		exit_cub3d(-1, "door left out in the open");
	else if (map[i][j] == 'I')
		add_sprite(cub3d, map, i, j);
	else if (is_start_pos(map[i][j]))
		set_starting_pos(cub3d, map, i, j);
	else if (map[i][j] != '0' && map[i][j] != 'D')
		exit_cub3d(-1, "wrong map caracter");
}

void	map_parser(t_cub3d *cub3d)
{
	char	**map;
	char	*line;
	size_t	i;
	size_t	j;

	i = 1;
	map = cub3d->map_content;
	while (map[i])
	{
		j = 0;
		line = skip_space(map[i]);
		if (!*line)
			break ;
		while (map[i][j])
		{
			map_conditions(cub3d, map, i, j);
			j++;
		}
		i++;
	}
	finalize_map(cub3d, map, i);
}
