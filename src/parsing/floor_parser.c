/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:14:53 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/08 18:07:13 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*substr_to_comma(char **str)
{
	size_t	i;
	char	*number;
	char	*temp;

	i = 0;
	while ((*str)[i] && (*str)[i] != ',')
		i++;
	temp = pro_substr(*str, 0, i);
	if (!temp)
		exit_cub3d(ENOMEM, "couldn't malloc a substr to coma");
	*str = *str + i + ((*str)[i] != 0);
	i = 0;
	while (temp[i] && !ft_is_space(temp[i]))
		i++;
	number = pro_substr(temp, 0, i);
	temp = skip_space(&(temp[i]));
	if (*temp)
		exit_cub3d(-1, "extra content after floor colors");
	if (!number)
		exit_cub3d(ENOMEM, "couldn't malloc a substr to coma");
	ft_free_node(1, temp);
	return (number);
}

static void	get_color(char **line, int *color)
{
	char	*number;

	*line = skip_space(*line);
	number = substr_to_comma(line);
	if (!ft_str_is_integer(number, color))
		exit_cub3d(-1, "floor/ceiling color is not a valid number");
	if (*color < 0 || *color > 255)
		exit_cub3d(-1, "floor/ceiling color overflows");
	ft_free_node(1, number);
}

void	floor_parser(char *line, t_cub3d *cub3d,
	t_tx_type *texture, t_boolean ignore_err)
{
	if (!ft_strncmp(line, "F", 1) && ft_is_space(*(line + 1)))
	{
		if (cub3d->texture.floor_is_set)
			exit_cub3d(-1, "floor color already set");
		line = line + 1;
		get_color(&line, &cub3d->texture.floor.r);
		get_color(&line, &cub3d->texture.floor.g);
		get_color(&line, &cub3d->texture.floor.b);
		cub3d->texture.floor_is_set = TRUE;
		*texture = FLOOR;
	}
	else if (!ft_strncmp(line, "C", 1) && ft_is_space(*(line + 1)))
	{
		if (cub3d->texture.ceiling_is_set)
			exit_cub3d(-1, "ceiling color already set");
		line = line + 1;
		get_color(&line, &cub3d->texture.ceiling.r);
		get_color(&line, &cub3d->texture.ceiling.g);
		get_color(&line, &cub3d->texture.ceiling.b);
		cub3d->texture.ceiling_is_set = TRUE;
		*texture = CEILING;
	}
	
	// else if (ignore_err == FALSE)
	// {
	// 	exit_cub3d(-1, "wrong textures content");
	// }
	line = skip_space(line);
	if (*line && ignore_err == FALSE)
		exit_cub3d(-1, "extra content after floor/ceiling color");
}
