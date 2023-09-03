/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:59:15 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/03 14:28:01 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void create_door_data(t_cub3d *cub3d, int x, int y)
{
    t_door  *door;
    t_door 	**temp;

	door = ft_malloc(sizeof(t_door), m_info(NULL, 1, NULL, 0));
	if (!door)
		exit_cub3d(ENOMEM, "couldn't malloc for door");
	door->x = x;
	door->y = y;
	door->open = 0.0;
	door->opening = TRUE;
	temp = cub3d->door;
	cub3d->door = add_element_to_array(temp, &door, sizeof(t_door *));
	ft_free_node(1, temp);
}

void	open_door(t_cub3d *cub3d, t_door **open_doors)
{
    t_raycaster_data	*raycaster;
	int					x;
	int					y;

	raycaster = &cub3d->raycaster;
	x = raycaster->player_x + 0.5 * raycaster->direction_x;
	y = raycaster->player_y + 0.5 * raycaster->direction_y;
	if (cub3d->mini_map[y][x] != 'D')
		return ;
	while (open_doors && *open_doors)
	{
		if ((*open_doors)->x == x && (*open_doors)->y == y)
		{
			if ((*open_doors)->open > 1)
			{
				(*open_doors)->opening = FALSE;
				(*open_doors)->open = 1.01;
			}
			return ;
		}
		open_doors++;
	}
    create_door_data(cub3d, x , y);
}

static t_boolean	delete_closed_door(t_cub3d *cub3d, t_door ***doors, int i)
{
	if ((*doors)[i]->open < -0.01)
	{
		cub3d->door = rm_element_from_array(*doors, *doors + i, sizeof(t_door *));
		ft_free_node(1, (*doors)[i]);
		ft_free_node(1, *doors);
		*doors = cub3d->door;
		return (TRUE);
	}
	return (FALSE);
}

void	animate_doors(t_cub3d *cub3d, t_door **doors)
{
	int     i;
	float	step;

	if (!doors)
		return ;
	i = 0;
	step = 0.03;
	while (doors[i])
	{
		if (delete_closed_door(cub3d, &doors, i))
			continue ;
		else if (doors[i]->open > 2)
			doors[i]->opening = FALSE;
		if (!(cub3d->raycaster.player_y + HB_RADIUS > (double) doors[i]->y && cub3d->raycaster.player_y - HB_RADIUS < (double) doors[i]->y + 1
			&& cub3d->raycaster.player_x + HB_RADIUS > (double) doors[i]->x && cub3d->raycaster.player_x - HB_RADIUS < (double) doors[i]->x + 1))
		{
            if (doors[i]->opening)
                doors[i]->open += step;
            else
                doors[i]->open -= step;
		}
		i++;
	}
}