/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:58:59 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/03 20:59:38 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_boolean	is_open_door(t_door **doors, int x, int y, float *door_open_ratio)
{
	int i;

	i = 0;
	if (!doors)
		return (FALSE);
	while (doors[i])
	{
		if (doors[i]->y == y && doors[i]->x == x)
		{
			if (door_open_ratio)
				*door_open_ratio = doors[i]->open;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
