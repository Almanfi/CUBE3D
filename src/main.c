/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:55:41 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/07 15:55:22 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef enum e_side
{
    UP,
    DOWN,
    LEFT,
    RIGHT
}   t_side;

typedef struct s_point
{
    int     x;
    int     y;
    t_side  side;
}   t_point;

typedef struct s_wall
{
    t_side  side;
    int     s;
    int     from;
    int     to;
}   t_wall;

t_wall wall_info(t_side side, int s, int from, int to)
{
    t_wall wall;

    wall.side = side;
    wall.s = s;
    wall.from = from;
    wall.to = to;
    return (wall);
}




static void find_corners(char **map, int i , int j, t_side side)
{
    if (map[i][j] == '1')
        map[i][j] = '2';
    else
        return;
    // if (map[i][j - 1] != '1' && map[i - 1][j] != '1' && map[i][j - 1] != '2' && map[i - 1][j] != '2')
    //     printf("Up_left corner %d, %d\n", j , i - 1);
    // if (map[i - 1][j] != '1' && map[i][j + 1] != '1' && map[i - 1][j] != '2' && map[i][j + 1] != '2')
    //     printf("Up_right corner %d, %d\n", j + 1 , i - 1);
    // if (map[i][j + 1] != '1' && map[i + 1][j] != '1' && map[i][j + 1] != '2' && map[i + 1][j] != '2')
    //     printf("Down_right corner %d, %d\n", j + 1 , i);
    // if (map[i + 1][j] != '1' && map[i][j - 1] != '1' && map[i + 1][j] != '2' && map[i][j - 1] != '2')
    //     printf("Down_left corner %d, %d\n", j , i);
    // if (map[i - 1][j - 1] != '1' && map[i - 1][j - 1] != '2' && (map[i - 1][j] == '1' || map[i - 1][j] == '2') && (map[i][j - 1] == '1' || map[i][j - 1] == '2'))
    //     printf("inside Up_left corner %d, %d\n", j , i - 1);
    // if (map[i - 1][j + 1] != '1' && map[i - 1][j + 1] != '2' && (map[i - 1][j] == '1' || map[i - 1][j] == '2') && (map[i][j + 1] == '1' || map[i][j + 1] == '2'))
    //     printf("inside Up_right corner %d, %d\n", j + 1 , i - 1);
    // if (map[i + 1][j + 1] != '1' && map[i + 1][j + 1] != '2' && (map[i][j + 1] == '1' || map[i][j + 1] == '2') && (map[i + 1][j] == '1' || map[i + 1][j] == '2'))
    //     printf("inside Down_right corner %d, %d\n", j + 1 , i);
    // if (map[i + 1][j - 1] != '1' && map[i + 1][j - 1] != '2' && (map[i][j - 1] == '1' || map[i][j - 1] == '2') && (map[i + 1][j] == '1' || map[i + 1][j] == '2'))
    //     printf("inside Down_left corner %d, %d\n", j , i);
    if (map[i][j + 1] == '1' && side != RIGHT)
        find_corners(map, i, j + 1, LEFT);
    if (map[i - 1][j] == '1' && side != DOWN)
        find_corners(map, i - 1, j, UP);
    if (map[i][j - 1] == '1' && side != LEFT)
        find_corners(map, i, j - 1, RIGHT);
    if (map[i + 1][j] == '1' && side != UP)
        find_corners(map, i + 1, j, DOWN);
        
}


t_point move_right(char **map, int *i , int *j, t_side *side)
{
    t_side sido;

    sido = *side;
    while (map[*i][*j] == '1' && map[(*i) - 1][*j] != '1')
    {
        // printf("move right\n");
        (*j)++;
    }
    if (map[*i][*j] == '1')
    {
        *side = UP;
        // printf("move up\n");
        (*i)--;
        // printf("inside right top corner x = %d, y = %d\n", (*j), (*i) + 1);
        return ((t_point){(*j), (*i) + 1, sido});
    }
    else
    {
        // printf("move left\n");
        (*j)--;
        *side = DOWN;
        // printf("right top corner x = %d, y = %d\n", (*j) + 1, (*i));
        return ((t_point){(*j) + 1, (*i), sido});
    }
}

t_point move_down(char **map, int *i , int *j, t_side *side)
{
    t_side sido;

    sido = *side;
    while (map[*i][*j] == '1' && map[*i][*j + 1] != '1')
    {
        // printf("move down\n");
        (*i)++;
    }
    if (map[*i][*j] == '1')
    {
        *side = RIGHT;
    //    printf("move right\n");
        (*j)++;
        // printf("inside down right corner x = %d, y = %d\n", (*j), (*i));
        return ((t_point){(*j), (*i), sido});
    }
    else
    {
        // printf("move up\n");
        (*i)--;
        *side = LEFT;
        // printf("down right corner x = %d, y = %d\n", (*j) + 1, (*i) + 1);
        return ((t_point){(*j) + 1, (*i) + 1, sido});
    }
}

t_point move_left(char **map, int *i , int *j, t_side *side)
{
    t_side sido;

    sido = *side;
    while (map[*i][*j] == '1' && map[(*i) + 1][*j] != '1')
    {
        // printf("move left\n");
        (*j)--;
    }
    if (map[*i][*j] == '1')
    {
        *side = DOWN;
        // printf("move down\n");
        (*i)++;
        // printf("inside left down corner x = %d, y = %d\n", (*j) + 1, (*i));
        return ((t_point){(*j) + 1, (*i), sido});
    }
    else
    {
        // printf("move right\n");
        (*j)++;
        *side = UP;
        // printf("left down corner x = %d, y = %d\n", (*j), (*i) + 1);
        return ((t_point){(*j), (*i) + 1, sido});
    }
}

t_point move_up(char **map, int *i , int *j, t_side *side)
{
    t_side sido;

    sido = *side;
    while (map[*i][*j] == '1' && map[*i][*j - 1] != '1')
    {
        // printf("move up\n");
        (*i)--; 
    }
    if (map[*i][*j] == '1')
    {
        *side = LEFT;
        // printf("move left\n");
        (*j)--;
        // printf("inside up left corner x = %d, y = %d\n", (*j) + 1, (*i) + 1);
        return ((t_point){(*j) + 1, (*i) + 1, sido});
    }
    else
    {
        // printf("move down\n");
        (*i)++;
        *side = RIGHT;
        // printf("up left corner x = %d, y = %d\n", (*j), (*i));
        return ((t_point){(*j), (*i), sido});
    }
}

t_side find_wall_side(t_side side)
{
    if (side == RIGHT)
        return (UP);
    else if (side == LEFT)
        return (DOWN);
    else if (side == DOWN)
        return (RIGHT);
    else
        return (LEFT);
}

void    sort_walls(t_point *point, int n)
{
    t_wall wall[100];
    int i;
    char *side_str;
    char **side_list;

    wall[0] = wall_info(find_wall_side(point[0].side), point[0].y, point[n].x, point[0].x);
    i = 1;
    while (i <= n)
    {
        if (point[i - 1].x == point[i].x && point[i].side == UP)
            wall[i] = wall_info(find_wall_side(point[i].side), point[i].x, point[i].y, point[i - 1].y);
        else if (point[i - 1].x == point[i].x && point[i].side == DOWN)
            wall[i] = wall_info(find_wall_side(point[i].side), point[i].x, point[i - 1].y, point[i].y);
        else if (point[i - 1].y == point[i].y && point[i].side == RIGHT)
            wall[i] = wall_info(find_wall_side(point[i].side), point[i].y, point[i - 1].x, point[i].x);
        else if (point[i - 1].y == point[i].y && point[i].side == LEFT)
            wall[i] = wall_info(find_wall_side(point[i].side), point[i].y, point[i].x, point[i - 1].x);
        i++;
    }
    side_str = "UP DOWN LEFT RIGHT";
    side_list = ft_split(side_str, ' ');
    i = 0;
    while (i <= n)
    {
        printf("wall side is %s \t, with constant %3d, from %3d, to %3d\n",
            side_list[wall[i].side], wall[i].s, wall[i].from, wall[i].to);
        i++;
    }
}

void follow_corners(char **map, int i , int j)
{
    t_side direction;
    int i0, j0;
    t_point pnt[100];
    int k;

    i0 = i;
    j0 = j;
    direction = RIGHT;
    ft_bzero(&pnt, sizeof(t_point) * 100);
    k = 0;
    while (TRUE)
    {
        if (direction == RIGHT)
            pnt[k] = move_right(map, &i, &j, &direction);
        else if (direction == DOWN)
            pnt[k] = move_down(map, &i, &j, &direction);
        else if (direction == LEFT)
            pnt[k] = move_left(map, &i, &j, &direction);
        else if (direction == UP)
            pnt[k] = move_up(map, &i, &j, &direction);
        if (direction == RIGHT && i == i0 && j == j0)
            break ;
        k++;
    }
    // i = 0;
    // while (i <= k)
    // {
    //     printf("corner x = %d, y = %d\n", pnt[i].x, pnt[i].y);
    //     i++;
    // }
    sort_walls(pnt, k);
}

static void switch_1_2(char **map, int i , int j)
{
    if (map[i][j] == '1')
        map[i][j] = '2';
    else
        return;
    // if (map[i][j - 1] != '1' && map[i - 1][j] != '1' && map[i][j - 1] != '2' && map[i - 1][j] != '2')
    //     printf("Up_left corner %d, %d\n", j , i - 1);
    // if (map[i - 1][j] != '1' && map[i][j + 1] != '1' && map[i - 1][j] != '2' && map[i][j + 1] != '2')
    //     printf("Up_right corner %d, %d\n", j + 1 , i - 1);
    // if (map[i][j + 1] != '1' && map[i + 1][j] != '1' && map[i][j + 1] != '2' && map[i + 1][j] != '2')
    //     printf("Down_right corner %d, %d\n", j + 1 , i);
    // if (map[i + 1][j] != '1' && map[i][j - 1] != '1' && map[i + 1][j] != '2' && map[i][j - 1] != '2')
    //     printf("Down_left corner %d, %d\n", j , i);
    // if (map[i - 1][j - 1] != '1' && map[i - 1][j - 1] != '2' && (map[i - 1][j] == '1' || map[i - 1][j] == '2') && (map[i][j - 1] == '1' || map[i][j - 1] == '2'))
    //     printf("inside Up_left corner %d, %d\n", j , i - 1);
    // if (map[i - 1][j + 1] != '1' && map[i - 1][j + 1] != '2' && (map[i - 1][j] == '1' || map[i - 1][j] == '2') && (map[i][j + 1] == '1' || map[i][j + 1] == '2'))
    //     printf("inside Up_right corner %d, %d\n", j + 1 , i - 1);
    // if (map[i + 1][j + 1] != '1' && map[i + 1][j + 1] != '2' && (map[i][j + 1] == '1' || map[i][j + 1] == '2') && (map[i + 1][j] == '1' || map[i + 1][j] == '2'))
    //     printf("inside Down_right corner %d, %d\n", j + 1 , i);
    // if (map[i + 1][j - 1] != '1' && map[i + 1][j - 1] != '2' && (map[i][j - 1] == '1' || map[i][j - 1] == '2') && (map[i + 1][j] == '1' || map[i + 1][j] == '2'))
    //     printf("inside Down_left corner %d, %d\n", j , i);
    if (map[i][j + 1] == '1')
        find_corners(map, i, j + 1, LEFT);
    if (map[i - 1][j] == '1')
        find_corners(map, i - 1, j, UP);
    if (map[i][j - 1] == '1')
        find_corners(map, i, j - 1, RIGHT);
    if (map[i + 1][j] == '1')
        find_corners(map, i + 1, j, DOWN);
        
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    t_cub3d cub3d;
    int x[100];
    int y[100];

    ft_bzero(&cub3d, sizeof(t_cub3d));
    cub3d_parser(argc, argv, &cub3d);
    int i, j, k;
    k = 0;
    i = 0;
    while (cub3d.mini_map[i])
    {
        j = 0;
        while (cub3d.mini_map[i][j])
        {
            if ((i != 0 && j != 0 && i < 10 && j != 14) && cub3d.mini_map[i][j] == '1')
            {
                printf("\033[0;31m%c\033[0m\t", cub3d.mini_map[i][j]);
                switch_1_2(cub3d.mini_map, i, j);
                x[k] = j;
                y[k] = i;
                k++;
            }
            else if (cub3d.mini_map[i][j] == '2')
                printf("\033[0;31m%c\033[0m\t", cub3d.mini_map[i][j]);
            else
                printf("%c\t", cub3d.mini_map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    i = 0;
    while (cub3d.mini_map[i])
    {
        j = 0;
        while (cub3d.mini_map[i][j])
        {
            if (cub3d.mini_map[i][j] == '2')
                cub3d.mini_map[i][j] = '1';
            j++;
        }
        i++;
    }
    i = 0;
    while (i < k)
    {
        follow_corners(cub3d.mini_map, y[i], x[i]);
        printf("______________________________________________________________\n");
        i++;
    }

    // printf("lines = %d, columns = %d\n", i, j);
    // i = 0;
    // find_corners(cub3d.map_content, y[0] + 1, x[0], RIGHT);
    // return (0);
    // while (i < k)
    // {
    //     printf("(%d, %d)\n", x[i], y[i]);
    //     i++;
    // }
}
