/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:13:43 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/30 13:15:36 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static  void    skip_empty_lines(t_cub3d *cub3d)
{
    char *line;
    t_boolean   start_wall;

    start_wall = FALSE;
    while (cub3d->map_content && !start_wall)
    {
        line = skip_space(*cub3d->map_content);
        while (*line && (*line == '1' || ft_is_space(*line)))
        {
            line++;
            if (!*line)
                start_wall = TRUE;
        }
        if (*line)
            exit_cub3d(-1, "surround map with walls");
        ft_free_node(1, *cub3d->map_content)
        cub3d->map_content++;
    }
    if (!start_wall)
        exit_cub3d(-1, "no map given");
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
            line = ft_malloc(max_len * sizeof(char));
            if (!line)
                exit_cub3d(ENOMEM, "couldn't malloc evened lines");
            temp = cub3d->map_content[i];
            cub3d->map_content[i] = ft_memcpy(line, temp, sizeof(char) * j);
            ft_free_node(GNL_SCOPE, temp);
            j--;
            while(j < max_len - 1)
                cub3d->map_content[i][j++] = ' ';
            cub3d->map_content[i][j++] = '\n';
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


void    map_parser(t_cub3d *cub3d)
{
    char    **map;
    size_t  i;
    size_t  j;

    skip_empty_lines(cub3d);
    justify_lines(cub3d);
    i = 0;
    map = cub3d->map_content;
    while (map[++i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '1' || ft_is_space(map[i][j]))
                ;
            else if (map[i][j] == '0' && (j == 0 ||
                ft_is_space(map[i - 1][j - 1]) || ft_is_space(map[i - 1][j]) || ft_is_space(map[i - 1][j + 1] ||)
                ft_is_space(map[i][j - 1]) || ft_is_space(map[i][j + 1]) ||
                ft_is_space(map[i + 1][j - 1]) || ft_is_space(map[i + 1][j]) || ft_is_space(map[i + 1][j + 1])))
                exit_cub3d(-1, "unvalid map due to unclosed walls");
            else if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
            {
                if (cub3d->player_set)
                    exit_cub3d(-1, "unvalid map due to mutiple player positions");
                else
                    cub3d->player_set = TRUE;
            }
            else
                exit_cub3d(-1, "wrong map caracter");
            j++;
        }
    }
}

