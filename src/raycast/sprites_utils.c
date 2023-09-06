/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:30:20 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/06 17:37:56 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	ft_swap(void **p1, void **p2)
{
	void	*temp;

	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void	rev_sort_sprites(t_sprite	**sprites)
{
	t_boolean	stop;
	size_t		i;
	size_t		j;

	if (!sprites)
		return ;
	i = -1;
	while (sprites[++i])
	{
		j = -1;
		stop = FALSE;
		while (sprites[++j])
		{
			if (sprites[j + 1]
				&& (sprites[j])->distance < (sprites[j + 1])->distance)
			{
				ft_swap((void **)(sprites + j), (void **)(sprites + j + 1));
				stop = TRUE;
			}
		}
		if (!stop)
			break ;
	}
}
