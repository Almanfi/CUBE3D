/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:38:14 by maboulkh          #+#    #+#             */
/*   Updated: 2023/09/06 17:46:58 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	corner_y(t_cub3d *cub3d, t_projected_point *p, double a, double b)
{
	if (p->y < 0)
	{
		p->y = 0;
		p->x = (p->y - b) / a;
	}
	else if (p->y > cub3d->minimap.height)
	{
		p->y = cub3d->minimap.height;
		p->x = (p->y - b) / a;
	}
}

static void	corner_x(t_cub3d *cub3d, t_projected_point *p, double a, double b)
{
	if (p->x < 0)
	{
		p->x = 0;
		p->y = a * p->x + b;
	}
	else if (p->x > cub3d->minimap.width)
	{
		p->x = cub3d->minimap.width;
		p->y = a * p->x + b;
	}
}

void	get_new_points(t_cub3d *cub3d, t_projected_point *p1,
		t_projected_point *p2)
{
	double	a;
	double	b;

	a = 10000000;
	if (p2->x - p1->x)
		a = (double)(p2->y - p1->y) / (double)(p2->x - p1->x);
	b = p1->y - a * p1->x;
	corner_x(cub3d, p1, a, b);
	corner_y(cub3d, p1, a, b);
	corner_x(cub3d, p2, a, b);
	corner_y(cub3d, p2, a, b);
}

void	pointer_swap(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	double_swap(double *a, double *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
