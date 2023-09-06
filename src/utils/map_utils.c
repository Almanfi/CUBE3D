/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:29:31 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/06 18:43:36 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*copy_line_and_fill(char *line, size_t len)
{
	size_t	i;
	char	*new_line;

	i = ft_strlen(line);
	if (i < len)
	{
		new_line = ft_malloc((len + 1) * sizeof(char), (t_mem_param){0,
				GNL_SCOPE, NULL, 0});
		if (!new_line)
			exit_cub3d(ENOMEM, "couldn't malloc filled lines");
		if (line)
			new_line = ft_memmove(new_line, line, sizeof(char) * i);
		ft_free_node(GNL_SCOPE, line);
		while (i < len)
			new_line[i++] = ' ';
		new_line[i] = 0;
		return (new_line);
	}
	return (line);
}

static void	fill_lines(t_cub3d *cub3d, size_t max_len)
{
	char	**temp_content;
	size_t	i;

	i = 0;
	cub3d->map_content[i] = copy_line_and_fill(NULL, max_len);
	while (cub3d->map_content[i])
	{
		cub3d->map_content[i] = copy_line_and_fill(cub3d->map_content[i],
				max_len);
		i++;
	}
	temp_content = cub3d->map_content;
	cub3d->map_content = add_element_to_array(cub3d->map_content,
			&cub3d->map_content[0], sizeof(char *));
	if (!cub3d->map_content)
		exit_cub3d(ENOMEM, "couldn't malloc justified map");
	ft_free_node(1, temp_content);
}

void	skip_empty_lines(t_cub3d *cub3d)
{
	char	*line;

	while (*cub3d->map_content)
	{
		line = skip_space(*cub3d->map_content);
		if (*line)
		{
			cub3d->map_content--;
			cub3d->content_len--;
			break ;
		}
		cub3d->map_content++;
		cub3d->content_len++;
	}
}

void	justify_lines(t_cub3d *cub3d)
{
	size_t	i;
	size_t	j;
	size_t	max_len;

	i = 0;
	max_len = 0;
	while (cub3d->map_content[i])
	{
		j = ft_strlen(cub3d->map_content[i++]);
		if (max_len < j)
			max_len = j;
	}
	fill_lines(cub3d, max_len);
}

t_boolean	open_wall(char **map, size_t i, size_t j)
{
	if (ft_is_space(map[i - 1][j]) || ft_is_space(map[i + 1][j])
			|| ft_is_space(map[i][j - 1]) || ft_is_space(map[i][j + 1]))
		return (TRUE);
	return (FALSE);
}
