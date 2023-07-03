/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:13:43 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/03 19:02:39 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static  void    skip_empty_lines(t_cub3d *cub3d)
{
    char *line;

    while (*cub3d->map_content)
    {
        line = skip_space(*cub3d->map_content);
        if (*line)
        {
            printf("broke here  |%s|\n", line);
            cub3d->map_content--;
            break;
        }
        cub3d->map_content++;
    }
}

static  void    fill_short_lines(size_t max_len, t_cub3d *cub3d)
{
    char    *line;
    char    *temp;
    size_t  i;
    size_t  j;

    i = 0;
    while (cub3d->map_content[i])
    {
        j = ft_strlen(cub3d->map_content[i]);
        if (j < max_len)
        {
            line = ft_malloc((max_len + 1)* sizeof(char), (t_mem_param){0,GNL_SCOPE, NULL, 0});
            if (!line)
                exit_cub3d(ENOMEM, "couldn't malloc evened lines");
            temp = cub3d->map_content[i];
            cub3d->map_content[i] = ft_memmove(line, temp, sizeof(char) * j);
            ft_free_node(GNL_SCOPE, temp);
            while(j < max_len)
                cub3d->map_content[i][j++] = ' ';
            cub3d->map_content[i][j] = 0;
        }
        i++;
    }
}

static  void    justify_lines(t_cub3d *cub3d)
{
    size_t  i;
    size_t  j;
    size_t  max_len;
    
    i = 0;
    max_len = 0;
    while (cub3d->map_content[i])
    {
        j = ft_strlen(cub3d->map_content[i++]);
        if (max_len < j)
            max_len = j;
    }
    fill_short_lines(max_len, cub3d);
}   

static t_boolean is_start_pos(char c)
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
        printf("the line |%s|\n", line);
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
    if (!cub3d->player_set)
        exit_cub3d(-1, "starting player position is mandatory");
    cub3d->map_content += i;
    skip_empty_lines(cub3d);
    printf("the finale line |%s|\n", *cub3d->map_content);
    if (*cub3d->map_content)
        exit_cub3d(-1, "garbage value after map");
}

