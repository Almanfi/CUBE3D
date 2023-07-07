/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:13:43 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/07 13:02:05 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_boolean is_start_pos(char c)
{
    if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
        return TRUE;
    return FALSE;
}

static  t_boolean open_wall(char **map, size_t i, size_t j)
{
    if (ft_is_space(map[i - 1][j - 1]) || ft_is_space(map[i - 1][j]) || ft_is_space(map[i - 1][j + 1])
        || ft_is_space(map[i][j - 1]) || ft_is_space(map[i][j + 1]) ||
        ft_is_space(map[i + 1][j - 1]) || ft_is_space(map[i + 1][j]) || ft_is_space(map[i + 1][j + 1]))
        return TRUE;
    return FALSE;
}

static void set_mini_map(t_cub3d *cub3d, size_t last_line)
{
    size_t i;
    
    cub3d->mini_map = ft_malloc(sizeof(char *) * last_line,
        (t_mem_param){NULL, 1, NULL, 0});
    if (!cub3d->mini_map)
        exit_cub3d(ENOMEM, "couldn't malloc the mini map");
    i = 0;
    while (i < last_line - 1)
    {
        cub3d->mini_map[i] = cub3d->map_content[i + 1];
        i++;
    }
    cub3d->mini_map[i] = NULL;
}

void    map_parser(t_cub3d *cub3d)
{
    char    **map;
    char    *line;
    size_t  i;
    size_t  j;

    skip_empty_lines(cub3d);
    if (!*cub3d->map_content)
        exit_cub3d(-1, "no map given");
    justify_lines(cub3d);
    i = 1;
    map = cub3d->map_content;
    while (map[i])
    {
        j = 0;
        line = skip_space(map[i]);
        if (!*line)
            break;
        while (map[i][j])
        {
            if (map[i][j] == '1' || ft_is_space(map[i][j]))
                ;
            else if ((map[i][j] == '0' ||  is_start_pos(map[i][j])) && (j == 0 || open_wall(map, i, j)))
                exit_cub3d(-1, "unvalid map due to unclosed walls");
            else if (is_start_pos(map[i][j]))
            {
                if (cub3d->player_set)
                    exit_cub3d(-1, "unvalid map due to mutiple player positions");
                else
                    cub3d->player_set = TRUE;
            }
            else if (map[i][j] != '0')
                exit_cub3d(-1, "wrong map caracter");
            j++;
        }
        i++;
    }
    cub3d->map_content += i;
    skip_empty_lines(cub3d);
    if (*cub3d->map_content)
        exit_cub3d(-1, "garbage value after map");
    if (!cub3d->player_set)
        exit_cub3d(-1, "starting player position is mandatory");
    cub3d->map_content = map;
    set_mini_map(cub3d, i);
}

