/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:31:04 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/09 18:51:16 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub3d *cub3d, int x, int y, int dimensions)
{
	int	temp_y;
	int temp_x;

	temp_y = y;
	temp_x = x;
	while (x < temp_x + dimensions)
	{
		y = temp_y;
		while (y < temp_y + dimensions)
		{
			cub3d_pixel_put(cub3d, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}

void    set_starting_position(t_cub3d *cub3d)
{
    size_t	i;
	size_t	j;
	char	**map;

	i = 0;
	map = cub3d->mini_map;
	while (map[i])
	{
		j = 0;
		while(map[i][j] && !is_start_pos(map[i][j]))
			j++;
		if (is_start_pos(map[i][j]))
			break;
		i++;
	}
	cub3d->raycaster.player_x = j;
	cub3d->raycaster.player_y = i;
	cub3d->raycaster.direction_x = -1;
	cub3d->raycaster.direction_y = 0;
	cub3d->raycaster.camera_x = 0;
	cub3d->raycaster.camera_y = 0.66;
}

void	draw_map(t_cub3d *cub3d)
{
	size_t	i;
	size_t	j;
	char	**map;

	i = 0;
	map = cub3d->mini_map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(cub3d, j * CUBE_DIMENSIONS, i * CUBE_DIMENSIONS, CUBE_DIMENSIONS);
			j++;
		}
		i++;
	}
}
double ft_abs(double value)
{
	if (value >= 0)
		return value;
	return (-value);
}

static void	set_ray_step(t_cub3d *cub3d)
{
	t_raycaster_data *raycaster;

	raycaster = &cub3d->raycaster;
	if (raycaster->rayX < 0)
	{
		raycaster->step_x = -1;
		raycaster->sideDistX = (raycaster->player_x - raycaster->mapX) * raycaster->deltadistX;
	}
	else
	{
		raycaster->step_x = 1;
		raycaster->sideDistX = (raycaster->mapX + 1.0 - raycaster->player_x) * raycaster->deltadistX;
	}
	if (raycaster->rayY < 0)
	{
		raycaster->step_y = -1;
		raycaster->sideDistY = (raycaster->player_y - raycaster->mapY) * raycaster->deltadistY;
	}
	else
	{
		raycaster->step_y = 1;
		raycaster->sideDistY = (raycaster->mapY + 1.0 - raycaster->player_y) * raycaster->deltadistY;
	}
}

static	void	perform_dda(t_cub3d *cub3d)
{
	t_raycaster_data *raycaster;

	raycaster = &cub3d->raycaster;
	while (!raycaster->hit)
	{
		if (raycaster->sideDistX < raycaster->sideDistY)
		{
			raycaster->sideDistX += raycaster->deltadistX;
			raycaster->mapX += raycaster->step_x;
			raycaster->side = FALSE;
		}
		else
		{
			raycaster->sideDistY += raycaster->deltadistY;
			raycaster->mapY += raycaster->step_y;
			raycaster->side = TRUE;
		}
		if (cub3d->mini_map[raycaster->mapY][raycaster->mapX] != '0'
			&& !is_start_pos(cub3d->mini_map[raycaster->mapY][raycaster->mapX]))
			raycaster->hit = TRUE;
	}
}

static	void draw_vertical_line(size_t x, t_cub3d *cub3d, int color)
{
	t_raycaster_data *raycaster;

	raycaster = &cub3d->raycaster;
	while (raycaster->draw_start < raycaster->draw_end)
	{
		cub3d_pixel_put(cub3d,(int) x, raycaster->draw_start, color);
		printf("in here\n");
		raycaster->draw_start++;
	}
}

static	void draw_wall(t_cub3d *cub3d, size_t x, int color)
{
	int line_height;

	line_height = (int) (WINDOW_HEIGHT / cub3d->raycaster.perpwallDist);
	printf("line height %d\n", line_height);
	cub3d->raycaster.draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (cub3d->raycaster.draw_start < 0)
		cub3d->raycaster.draw_start = 0;
	cub3d->raycaster.draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (cub3d->raycaster.draw_end >= WINDOW_HEIGHT)
		cub3d->raycaster.draw_end = WINDOW_HEIGHT - 1;
	draw_vertical_line(x, cub3d, color);
}

void	cast_rays(t_cub3d *cub3d)
{
	size_t	i;
	double	projected_ray;
	t_raycaster_data	*raycaster;

	raycaster = &cub3d->raycaster;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		raycaster->hit = FALSE;
		projected_ray = ((2 * i) / (double) WINDOW_WIDTH) - 1;
		printf("projected ray %lf\n", projected_ray);
		raycaster->rayX = raycaster->direction_x + raycaster->camera_x * projected_ray;
		raycaster->rayY = raycaster->direction_y + raycaster->camera_y * projected_ray;
		raycaster->mapX = raycaster->player_x;
		raycaster->mapY = raycaster->player_y;
		raycaster->deltadistX = raycaster->rayX ? LONG_MAX : ft_abs(1 / raycaster->rayX);
		raycaster->deltadistY = raycaster->rayY ? LONG_MAX : ft_abs(1 / raycaster->rayY);
		set_ray_step(cub3d);
		perform_dda(cub3d);
		if (!raycaster->side)
			raycaster->perpwallDist = raycaster->sideDistX - raycaster->deltadistX;
		else
			raycaster->perpwallDist = raycaster->sideDistY - raycaster->deltadistY;
		draw_wall(cub3d, i, 0xFFFFFF);
		i++;
	}
}

void	draw_cub3d(t_cub3d *cub3d)
{
	cub3d_window_init(cub3d);
	cub3d_frame_init(cub3d);
	set_starting_position(cub3d);
	cast_rays(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->frame.img, 0, 0);
}

