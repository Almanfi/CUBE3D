/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:38:26 by maboulkh          #+#    #+#             */
/*   Updated: 2023/08/22 17:00:52 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static t_boolean	cub3d_draw_steep_line(t_cub3d *cub3d, double y, double x, int color)
{
	cub3d_pixel_put(cub3d, y - 1, x, color);
	cub3d_pixel_put(cub3d, y, x, color);
	return (TRUE);
}

static t_boolean	cub3d_draw_normal_line(t_cub3d *cub3d, double x, double y, int color)
{
	cub3d_pixel_put(cub3d, x, y - 1, color);
	cub3d_pixel_put(cub3d, x, y, color);
	return (TRUE);
}

static void	cub3d_draw_line_pixels(t_cub3d *cub3d,
				t_projected_point p1, t_projected_point p2, t_boolean steep)
{
	double	grad;
	int		dx;
	int		color;

	grad = 1;
	if (p2.x - p1.x)
		grad = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	dx = 0;
	while (p1.x + dx < p2.x)
	{
		color = 0x00ff;
		if (steep)
			cub3d_draw_steep_line(cub3d, p1.y, p1.x + dx, color);
		else
			cub3d_draw_normal_line(cub3d, p1.x + dx, p1.y, color);
		p1.y += grad;
		dx++;
	}
}

void	cub3d_draw_line(t_cub3d *cub3d, t_projected_point point1,
		t_projected_point point2)
{
	t_boolean				steep;
	t_projected_point	*p1;
	t_projected_point	*p2;

	p1 = &point1;
	p2 = &point2;
	steep = ft_abs(p2->x - p1->x) < ft_abs(p2->y - p1->y);
	if (steep)
	{
		double_swap(&p2->x, &p2->y);
		double_swap(&p1->x, &p1->y);
	}
	if (p1->x > p2->x)
		pointer_swap((void **)&p1, (void **)&p2);
	cub3d_draw_line_pixels(cub3d, *p1, *p2, steep);
}