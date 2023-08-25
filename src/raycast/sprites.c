/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:28:35 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/25 00:40:32 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void     ft_swap(int **p1, int **p2)
{
    int *temp;

    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

static void    rev_sort_sprites(t_cub3d *cub3d)
{
    t_sprite **outer_loop;   
    t_sprite **iner_loop;
    t_boolean   stop;
    t_sprite    *temp;
    size_t      i;

    if (!cub3d->sprites)
        return;
    outer_loop = cub3d->sprites;
    while(*outer_loop)
    {
        iner_loop = cub3d->sprites;
        stop = FALSE;
        while (*iner_loop)
        {
            if (*(iner_loop + 1) && (*iner_loop)->distance > (*(iner_loop + 1))->distance)
            {
                ft_swap((int **)iner_loop , (int **) iner_loop + 1);
                stop = TRUE;
            }
            iner_loop++;
        }
        if (!stop)
            break;
        outer_loop++;
    }
    i = 0;
    while (i < cub3d->sprite_count / 2)
    {
        temp = cub3d->sprites[i];
        cub3d->sprites[i] = cub3d->sprites[cub3d->sprite_count - i - 1];
        cub3d->sprites[cub3d->sprite_count - i - 1] = temp;
        i++;
    }
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
		if (raycaster->mapX <= 0 || raycaster->mapY <= 0 || 
			raycaster->mapY > (int) cub3d->raycaster.rows_count || 
			raycaster->mapX > (int) cub3d->mini_map_line_len[raycaster->mapY]
			|| cub3d->mini_map[raycaster->mapY][raycaster->mapX] == '1'
			|| cub3d->mini_map[raycaster->mapY][raycaster->mapX] == 'D')
		{
			if (cub3d->mini_map[raycaster->mapY][raycaster->mapX] == 'D')
				raycaster->door = TRUE;
			raycaster->hit = TRUE;
		}
	}
}

void    draw_door_sprite(t_cub3d *cub3d, int id)
{
    t_sprite         **sprites;
    t_raycaster_data *raycaster;

    sprites = cub3d->sprites;
    (void) sprites;
    raycaster = &cub3d->raycaster;
    raycaster->sprite_x = cub3d->sprites[id]->x - raycaster->player_x;
    raycaster->sprite_y = cub3d->sprites[id]->y - raycaster->player_y;
    raycaster->inv_Det = 1.0 / (raycaster->camera_x * raycaster->direction_y
        - raycaster->direction_x * raycaster->camera_y);
    raycaster->transform_X = raycaster->inv_Det * (raycaster->direction_y * raycaster->sprite_x 
        - raycaster->direction_x * raycaster->sprite_y);
    raycaster->transform_Y = raycaster->inv_Det * ((-raycaster->camera_y) * raycaster->sprite_x
        + raycaster->camera_x * raycaster->sprite_y);
    // drawing the sprite
    raycaster->sprite_screenX = (int) ((WINDOW_WIDTH / 2) * (1 + raycaster->transform_X / raycaster->transform_Y));
    raycaster->sprite_width = 1.5 * ft_abs((int) WINDOW_HEIGHT / raycaster->transform_Y);
    raycaster->draw_startX = -raycaster->sprite_width / 2 + raycaster->sprite_screenX;
    if (raycaster->draw_startX < 0)
        raycaster->draw_startX = 0;
    raycaster->draw_endX = raycaster->sprite_width /2 + raycaster->sprite_screenX;
    if (raycaster->draw_endX >= WINDOW_WIDTH)
        raycaster->draw_endX = WINDOW_WIDTH - 1;


    int	i;
	double	projected_ray;

	i = raycaster->draw_startX + (raycaster->draw_endX - raycaster->draw_startX) / 2;
	while (i < raycaster->draw_endX)
	{
		raycaster->door = FALSE;
		raycaster->hit = FALSE;
		projected_ray = ((2 * i) / (double) WINDOW_WIDTH) - 1;
		raycaster->rayX = raycaster->direction_x + raycaster->camera_x * projected_ray;
		raycaster->rayY = raycaster->direction_y + raycaster->camera_y * projected_ray;
		raycaster->mapX = raycaster->player_x;
		raycaster->mapY = raycaster->player_y;
		raycaster->deltadistX = raycaster->rayX == 0.0 ? DBL_MAX : ft_abs((double) 1 / raycaster->rayX);
		raycaster->deltadistY = raycaster->rayY == 0.0 ? DBL_MAX : ft_abs((double) 1 / raycaster->rayY);
		set_ray_step(cub3d);
		perform_dda(cub3d);
		if (!raycaster->side)
        {
            raycaster->sideDistX += 0.5 * raycaster->deltadistX;
			raycaster->perpwallDist = raycaster->sideDistX - raycaster->deltadistX;
        }
		else
        {
            raycaster->sideDistY += 0.5 * raycaster->deltadistY;
            raycaster->perpwallDist = raycaster->sideDistY - raycaster->deltadistY;
        }
		if (raycaster->perpwallDist < 0.1)
			raycaster->perpwallDist = 0.1;
		cub3d->Zbuffer[i] = raycaster->perpwallDist;
		// draw_wall(cub3d, i);
		i++;
	}
}

void    draw_other_sprite(t_cub3d *cub3d, int id)
{
    t_sprite **sprites;
    t_raycaster_data *raycaster;
    int               stripe;
    int               row;
    int               tex_d;

    sprites = cub3d->sprites;
    (void) sprites;
    raycaster = &cub3d->raycaster;
    raycaster->sprite_x = cub3d->sprites[id]->x - raycaster->player_x;
    raycaster->sprite_y = cub3d->sprites[id]->y - raycaster->player_y;
    raycaster->inv_Det = 1.0 / (raycaster->camera_x * raycaster->direction_y
        - raycaster->direction_x * raycaster->camera_y);
    raycaster->transform_X = raycaster->inv_Det * (raycaster->direction_y * raycaster->sprite_x 
        - raycaster->direction_x * raycaster->sprite_y);
    raycaster->transform_Y = raycaster->inv_Det * ((-raycaster->camera_y) * raycaster->sprite_x
        + raycaster->camera_x * raycaster->sprite_y);
    // drawing the sprite
    raycaster->sprite_screenX = (int) ((WINDOW_WIDTH / 2) * (1 + raycaster->transform_X / raycaster->transform_Y));

    raycaster->sprite_height = ft_abs((int) WINDOW_HEIGHT / raycaster->transform_Y);
    raycaster->draw_startY  = -raycaster->sprite_height / 2 + WINDOW_HEIGHT / 2;
    if (raycaster->draw_startY < 0)
        raycaster->draw_startY = 0;
    raycaster->draw_endY = raycaster->sprite_height / 2 + WINDOW_HEIGHT / 2;
    if (raycaster->draw_startY >= WINDOW_HEIGHT)
        raycaster->draw_endY = WINDOW_HEIGHT - 1;

    raycaster->sprite_width = ft_abs((int) WINDOW_HEIGHT / raycaster->transform_Y);
    raycaster->draw_startX = -raycaster->sprite_width / 2 + raycaster->sprite_screenX;
    if (raycaster->draw_startX < 0)
        raycaster->draw_startX = 0;
    raycaster->draw_endX = raycaster->sprite_width /2 + raycaster->sprite_screenX;
    if (raycaster->draw_endX >= WINDOW_WIDTH)
        raycaster->draw_endX = WINDOW_WIDTH - 1;
    stripe = raycaster->draw_startX;
    while(stripe < raycaster->draw_endX)
    {
        raycaster->texX = ((int) (256 * (stripe - (-raycaster->sprite_width / 2 + raycaster->sprite_screenX))
            * TEX_DIMENSIONS / raycaster->sprite_width)) / 256;
        if (raycaster->transform_Y > 0 && stripe > 0 && stripe < WINDOW_WIDTH && raycaster->transform_Y < cub3d->Zbuffer[stripe])
        {
            row = raycaster->draw_startY;
            while (row < raycaster->draw_endY)
            {
                tex_d = row * 256 - WINDOW_HEIGHT * 128 + raycaster->sprite_height * 128;
                raycaster->texY = ((tex_d * TEX_DIMENSIONS) / raycaster-> sprite_height) / 256;
                if ((cub3d->texture.tx[FIREHEAD1 + cub3d->texturen][TEX_DIMENSIONS * raycaster->texY + raycaster->texX] & 0x00FFFFFF) != 0)
                    cub3d_pixel_put(cub3d, stripe, row,
                    cub3d->texture.tx[FIREHEAD1 + cub3d->texturen][TEX_DIMENSIONS * raycaster->texY + raycaster->texX]);
                row++;
            }
            
        }
        stripe++;
    }
}


void    draw_sprites(t_cub3d *cub3d)
{
    t_sprite **sprites;
    t_raycaster_data *raycaster;
    size_t            i;
    // int               stripe;
    // int               row;
    // int               tex_d;

    sprites = cub3d->sprites;
    raycaster = &cub3d->raycaster;
    while (sprites && *sprites)
    {
        (*sprites)->distance = ((raycaster->player_x - (*sprites)->x) * (raycaster->player_x - (*sprites)->x) +
            (raycaster->player_y - (*sprites)->y) * (raycaster->player_y - (*sprites)->y));
        sprites++;
    }
    rev_sort_sprites(cub3d);
    i = 0;
    sprites = cub3d->sprites;
    while(i < cub3d->sprite_count)
    {
        if (cub3d->sprites[i]->sprite_id == DOOR)
            draw_door_sprite(cub3d, i);
        else
            draw_other_sprite(cub3d, i);
        
        // if (cub3d->sprites[i]->sprite_id == DOOR)
        // {
        //     i++;
        //     continue;
        // }
        // raycaster->sprite_x = cub3d->sprites[i]->x - raycaster->player_x;
        // raycaster->sprite_y = cub3d->sprites[i]->y - raycaster->player_y;
        // raycaster->inv_Det = 1.0 / (raycaster->camera_x * raycaster->direction_y
        //     - raycaster->direction_x * raycaster->camera_y);
        // raycaster->transform_X = raycaster->inv_Det * (raycaster->direction_y * raycaster->sprite_x 
        //     - raycaster->direction_x * raycaster->sprite_y);
        // raycaster->transform_Y = raycaster->inv_Det * ((-raycaster->camera_y) * raycaster->sprite_x
        //     + raycaster->camera_x * raycaster->sprite_y);
        // // drawing the sprite
        // raycaster->sprite_screenX = (int) ((WINDOW_WIDTH / 2) * (1 + raycaster->transform_X / raycaster->transform_Y));

        // raycaster->sprite_height = ft_abs((int) WINDOW_HEIGHT / raycaster->transform_Y);
        // raycaster->draw_startY  = -raycaster->sprite_height / 2 + WINDOW_HEIGHT / 2;
        // if (raycaster->draw_startY < 0)
        //     raycaster->draw_startY = 0;
        // raycaster->draw_endY = raycaster->sprite_height / 2 + WINDOW_HEIGHT / 2;
        // if (raycaster->draw_startY >= WINDOW_HEIGHT)
        //     raycaster->draw_endY = WINDOW_HEIGHT - 1;

        // raycaster->sprite_width = ft_abs((int) WINDOW_HEIGHT / raycaster->transform_Y);
        // raycaster->draw_startX = -raycaster->sprite_width / 2 + raycaster->sprite_screenX;
        // if (raycaster->draw_startX < 0)
        //     raycaster->draw_startX = 0;
        // raycaster->draw_endX = raycaster->sprite_width /2 + raycaster->sprite_screenX;
        // if (raycaster->draw_endX >= WINDOW_WIDTH)
        //     raycaster->draw_endX = WINDOW_WIDTH - 1;
        // stripe = raycaster->draw_startX;
        // while(stripe < raycaster->draw_endX)
        // {
        //     raycaster->texX = ((int) (256 * (stripe - (-raycaster->sprite_width / 2 + raycaster->sprite_screenX))
        //         * TEX_DIMENSIONS / raycaster->sprite_width)) / 256;
        //     if (raycaster->transform_Y > 0 && stripe > 0 && stripe < WINDOW_WIDTH && raycaster->transform_Y < cub3d->Zbuffer[stripe])
        //     {
        //         row = raycaster->draw_startY;
        //         while (row < raycaster->draw_endY)
        //         {
        //             tex_d = row * 256 - WINDOW_HEIGHT * 128 + raycaster->sprite_height * 128;
        //             raycaster->texY = ((tex_d * TEX_DIMENSIONS) / raycaster-> sprite_height) / 256;
        //             if ((cub3d->texture.tx[FIREHEAD1 + cub3d->texturen][TEX_DIMENSIONS * raycaster->texY + raycaster->texX] & 0x00FFFFFF) != 0 && cub3d->sprites[i]->sprite_id != DOOR)
        //                 cub3d_pixel_put(cub3d, stripe, row,
        //                 cub3d->texture.tx[FIREHEAD1 + cub3d->texturen][TEX_DIMENSIONS * raycaster->texY + raycaster->texX]);
        //             // if ((cub3d->texture.tx[sprites[i]->sprite_id][TEX_DIMENSIONS * raycaster->texY + raycaster->texX] & 0x00FFFFFF) != 0)
        //             //     cub3d_pixel_put(cub3d, stripe, row,
        //             //     cub3d->texture.tx[sprites[i]->sprite_id][TEX_DIMENSIONS * raycaster->texY + raycaster->texX]);
        //             row++;
        //         }
                
        //     }
        //     stripe++;
        // }
        i++;
    }
}