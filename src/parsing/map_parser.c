/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:13:43 by bamrouch          #+#    #+#             */
/*   Updated: 2023/08/15 17:05:07 by maboulkh         ###   ########.fr       */
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

static size_t clamp_trailing_space(char *line)
{
    size_t len;
    size_t last_char;

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
    return last_char;
}

static void set_mini_map(t_cub3d *cub3d, size_t last_line)
{
    size_t i;
    size_t line_len;
    
    cub3d->mini_map = ft_malloc(sizeof(char *) * last_line,
        (t_mem_param){NULL, 1, NULL, 0});
    if (!cub3d->mini_map)
        exit_cub3d(ENOMEM, "couldn't malloc the mini map");
    i = 0;
    while (i < last_line - 1)
    {   
        cub3d->raycaster.rows_count++;
        cub3d->mini_map[i] = cub3d->map_content[i + 1];
        line_len = clamp_trailing_space(cub3d->mini_map[i]);
        cub3d->mini_map_line_len = add_element_to_array(cub3d->mini_map_line_len, &line_len, sizeof(size_t));
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
                map[i][j] = '0';
                cub3d->raycaster.player_x = j + 0.5;
                cub3d->raycaster.player_y = i - 0.5;
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

