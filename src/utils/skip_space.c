/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:14:37 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/05 16:39:31 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_boolean	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f'
		|| c == '\n')
		return (TRUE);
	return (FALSE);
}

char	*skip_space(char *str)
{
	if (!str)
		return (str);
	while (*str && ft_is_space(*str))
		str++;
	return (str);
}

size_t	clamp_trailing_space(char *line)
{
	size_t	len;
	size_t	last_char;

	last_char = 0;
	len = 0;
	while (line[len])
	{
		if (ft_is_space(line[len]))
			;
		else
			last_char = len;
		len++;
	}
	line[last_char + 1] = 0;
	return (last_char);
}
