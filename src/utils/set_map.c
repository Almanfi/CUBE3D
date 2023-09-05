/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:18:02 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/05 16:41:49 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_boolean	is_start_pos(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (TRUE);
	return (FALSE);
}

void	set_mini_map(t_cub3d *cub3d, size_t last_line)
{
	size_t	i;
	size_t	line_len;

	cub3d->mini_map = ft_malloc(sizeof(char *) * last_line, (t_mem_param){NULL,
			1, NULL, 0});
	if (!cub3d->mini_map)
		exit_cub3d(ENOMEM, "couldn't malloc the mini map");
	i = 0;
	while (i < last_line - 1)
	{
		cub3d->raycaster.rows_count++;
		cub3d->mini_map[i] = cub3d->map_content[i + 1];
		line_len = clamp_trailing_space(cub3d->mini_map[i]);
		cub3d->mini_map_line_len = add_element_to_array(
				cub3d->mini_map_line_len,
				&line_len, sizeof(size_t));
		i++;
	}
	cub3d->mini_map[i] = NULL;
}
