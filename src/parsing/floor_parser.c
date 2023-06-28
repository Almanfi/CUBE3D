/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:14:53 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/28 21:21:53 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	char	*substr_to_comma(char **str)
{
	size_t	i;
	char 	*number;
	char	*temp;

	i = 0;
	while ((*str)[i] && (*str)[i] != ',')
		i++;
	temp = pro_substr(str, 0, i - 1);
	if (!temp)
		exit_cub3d(ENOMEM, "couldn't malloc a substr to coma");
	*str = *str + i;
	i = 0;
	while (temp[i] && !ft_is_space(temp[i]))
		i++;
	number = pro_substr(temp, 0, i - 1);
	if (!number)
		exit_cub3d(ENOMEM, "couldn't malloc a substr to coma");
	ft_free_node(1, temp);
	return number;
}

static	void	get_color(char **line, int *color)
{
	char *number;

	*line = skip_space(*line);
	number = substr_to_comma(line);
	if (!ft_str_is_integer(number, color))
		exit_cub3d(-1, "floor color is not a valid number");
	if (*color < 0 || *color > 255)
		exit_cub3d(-1, "floor color overflows");
	ft_free_node(1, number);
}

void	floor_parser(char *line, t_cub3d *cub3d)
{
	char *number;

	if (!ft_strncmp(line, "F ", 2))
	{
		get_color(&(line + 1), &cub3d->texture.floor.r);
		get_color(&line, &cub3d->texture.floor.g);
		get_color(&line, &cub3d->texture.floor.b);
		line = skip_space(line);
		if (*line)
			exit_cub3d(-1, "extra content after floor color");
        cub3d->texture.floor_is_set = TRUE;
	}
    else
        exit_cub3d(-1, "wrong line content");
}

