/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:55:41 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/08 00:15:25 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



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

static void set_walls_type_in_data(t_cub3d *cub3d, t_wall *wall)
{
    t_wall *new_wall;
    t_wall **temp;
    t_wall ***wall_arr;

    if (wall->side == UP)
        wall_arr = &cub3d->walls.up;
    if (wall->side == DOWN)
        wall_arr = &cub3d->walls.down;
    if (wall->side == LEFT)
        wall_arr = &cub3d->walls.left;
    if (wall->side == RIGHT)
        wall_arr = &cub3d->walls.right;
    new_wall = ft_malloc(sizeof(t_wall), m_info(NULL, DATA_SCOPE, NULL, 0));
    ft_memcpy(new_wall, wall, sizeof(t_wall));
    temp = *wall_arr;
    *wall_arr = add_element_to_array(*wall_arr, &new_wall, sizeof(t_wall *));
    // ft_free_node(DATA_SCOPE, temp);
    ft_malloc(1, m_info(*wall_arr, DATA_SCOPE, NULL, 0));
    // printf("sorting wall side is %d \t, with constant %3d, from %3d, to %3d added to %p\n",
    //         wall->side, wall->s, wall->from, wall->to, wall_arr);
}

void    set_walls_type(t_cub3d *cub3d, t_point *point, int n)
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
        set_walls_type_in_data(cub3d, wall + i);
        printf("wall side is %s \t, with constant %3d, from %3d, to %3d\n",
            side_list[wall[i].side], wall[i].s, wall[i].from, wall[i].to);
        i++;
    }
}

void follow_corners(t_cub3d *cub3d, char **map, int i , int j)
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
    set_walls_type(cub3d, pnt, k);
}

static void switch_1_2(char **map, int i , int j)
{
    if (map[i][j] == '1')
        map[i][j] = '2';
    else
        return;
    if (map[i][j + 1] == '1')
        find_corners(map, i, j + 1, LEFT);
    if (map[i - 1][j] == '1')
        find_corners(map, i - 1, j, UP);
    if (map[i][j - 1] == '1')
        find_corners(map, i, j - 1, RIGHT);
    if (map[i + 1][j] == '1')
        find_corners(map, i + 1, j, DOWN);
        
}

void    get_walls(t_cub3d *cub3d)
{
    int x[100];
    int y[100];
    int i, j, k;
    k = 0;
    i = 0;
    while (cub3d->mini_map[i])
    {
        j = 0;
        while (cub3d->mini_map[i][j])
        {
            if ((i != 0 && j != 0 && i < 10 && j != 14) && cub3d->mini_map[i][j] == '1')
            {
                printf("\033[0;31m%c\033[0m\t", cub3d->mini_map[i][j]);
                switch_1_2(cub3d->mini_map, i, j);
                x[k] = j;
                y[k] = i;
                k++;
            }
            else if (cub3d->mini_map[i][j] == '2')
                printf("\033[0;31m%c\033[0m\t", cub3d->mini_map[i][j]);
            else
                printf("%c\t", cub3d->mini_map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    i = 0;
    while (cub3d->mini_map[i])
    {
        j = 0;
        while (cub3d->mini_map[i][j])
        {
            if (cub3d->mini_map[i][j] == '2')
                cub3d->mini_map[i][j] = '1';
            j++;
        }
        i++;
    }
    i = 0;
    while (i < k)
    {
        follow_corners(cub3d, cub3d->mini_map, y[i], x[i]);
        printf("______________________________________________________________\n");
        i++;
    }
}

void print_walls(t_wall **walls)
{
    int i;
    char *side_str;
    char **side_list;

    side_str = "UP DOWN LEFT RIGHT";
    side_list = ft_split(side_str, ' ');
    i = 0;
    if (walls[i])
        printf("______________printing %s walls____________\n", side_list[walls[i]->side]);
    while (walls[i])
    {
        printf("wall side is %s \t, with constant %3d, from %3d, to %3d\n",
            side_list[walls[i]->side], walls[i]->s, walls[i]->from, walls[i]->to);
        i++;
    }
    i = 0;
    while (side_list[i])
        free(side_list[i++]);
    free(side_list);
}

static void	sort_walls(t_wall **walls)
{
   int  i;
   int  j;
   t_wall *wall;

   i = 0;
    while (walls[i])
    {
        j = 0;
        while (walls[j + 1])
        {
            if (walls[j]->s > walls[j + 1]->s)
            {
                wall = walls[j];
                walls[j] = walls[j + 1];
                walls[j + 1] = wall;
            }
            j++;
        }
        i++;
    }
}

// line equation is => aX + bY + c = 0
void    calculate_lines_params(t_wall **walls)
{
    int     i;

    i = 0;
    while (walls[i])
    {
        // bY + c = 0
        if (walls[i]->side == UP || walls[i]->side == DOWN)
        {
            walls[i]->a = 0;
            walls[i]->b = 1;
            walls[i]->c = - walls[i]->s;
        }
        else // aX + c = 0
        {
            walls[i]->a = 1;
            walls[i]->b = 0;
            walls[i]->c = - walls[i]->s;
        }
        i++;
    }
}

void	do_all_walls(t_walls *walls, void (*fn) (t_wall **))
{
	fn(walls->up);
	fn(walls->down);
	fn(walls->left);
	fn(walls->right);
}

t_boolean   is_epsilon(float x)
{
    if (x < 0.000000000001 && x > - 0.000000000001)
        return (TRUE);
    return (FALSE);
}

// line equetion is => aX + bY + c = 0
t_wall    find_player_line_equation(t_player *player, int n)
{
    t_wall  wall;
    float   angle;

    if (n == 1)
        angle = player->a1;
    else if (n == 2)
        angle = player->a2;
    else
    {
        printf("error line number is wrong\n");
        exit(1);
    }
    printf("angle is = %.15f\n", angle);
    if (is_epsilon(angle - M_PI_2) || is_epsilon(angle + M_PI_2))
    {
        wall.a = 1;
        wall.b = 0;
        wall.c = - player->x;
    }
    else if (is_epsilon(angle - M_PI) || is_epsilon(angle))
    {
        wall.a = 0;
        wall.b = 1;
        wall.c = - player->y;
    }
    else
    {
        wall.a = - tan(angle);
        wall.b = 1;
        wall.c = - player->y + wall.a * player->x;
    }
    return (wall);
}

static t_boolean   find_line_intersect(t_wall *player, t_wall *wall)
{
    printf("wall equation is => |%f X + %f Y + %f = 0|\n", wall->a, wall->b, wall->c);
    printf("player line equation is => |%f X + %f Y + %f = 0|\n_______________\n", player->a, player->b, player->c);
    float   delta;
    float   x;
    float   y;

    delta = wall->a * player->b - wall->b * player->a;
    if (delta < 0.000000001 && delta > - 0.000000001) // this is iffy
    {
        printf("no intersection\n");
        return (FALSE);
    }
    x = (wall->c * player->b - wall->b * player->c) / delta;
    y = (wall->c * player->a - wall->a * player->c) / delta;
    printf("intersection at point (%f,%f)\n", x, y);
    return (TRUE);
}

static t_boolean   check_intersection(t_player *player, t_wall *wall)
{
    float   y;
    float   x1;
    float   x2;
    float   angle1;
    int     intersection;
    t_wall  player_line1;
    t_wall  player_line2;

    intersection = 0;
    y = wall->s;
    x1 = wall->from;
    x2 = wall->to;
    angle1 = atan((y - player->y) / (x1 - player->x));
    player_line1 = find_player_line_equation(player, 1);
    if (angle1 <= player->a1 && angle1 >= player->a2)
    {
        printf("point inside inside\n");
        intersection++;
    }
    if (find_line_intersect(&player_line1, wall))
        intersection++;
    angle1 = atan((y - player->y) / (x2 - player->x));
    player_line2 = find_player_line_equation(player, 2);
    if (angle1 <= player->a1 && angle1 >= player->a2)
    {
        printf("point inside inside\n");
        intersection++;
    }
    if (find_line_intersect(&player_line2, wall))
        intersection++;
    if (intersection > 1)
        return (TRUE);
    return (FALSE);
}

// static t_boolean   check_intersection(t_player *player, t_wall *wall)
// {
//     float   x;
//     float   y;
//     float   angle;
//     int     intersection;

//     intersection = 0;
//     if (wall->side == UP || wall->side == DOWN)
//     {
//         y = wall->s;
//         x = wall->from;
//         angle = atan((y - player->y) / (x - player->x));
//         if (angle <= player->a1 && angle >= player->a2)
//             intersection++;
//         x = wall->from;
//         angle = atan((y - player->y) / (x - player->x));
//         if (angle <= player->a1 && angle >= player->a2)
//             intersection++;
//         else if (find_line_intersect())
//     }
// }

void    find_intersections(t_cub3d *cub3d)
{
    t_player *player;

    player = &(cub3d->player);
    player->a1 = player->angle + (player->v_angle / 2);
    player->a2 = player->angle - (player->v_angle / 2);
    if (check_intersection(player, cub3d->walls.down[0]))
        printf("collsion detected\n");
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    t_cub3d cub3d;

    ft_bzero(&cub3d, sizeof(t_cub3d));
    cub3d_parser(argc, argv, &cub3d);
    get_walls(&cub3d);
    do_all_walls((&cub3d.walls), sort_walls);
    do_all_walls((&cub3d.walls), print_walls);
    do_all_walls((&cub3d.walls), calculate_lines_params);
    cub3d.player.x = 4;
    cub3d.player.y = 3;
    cub3d.player.angle = 0.01;
    cub3d.player.v_angle = M_PI;
    find_intersections(&cub3d);
    // sort_all_walls(&(cub3d.walls));
    // print_walls(cub3d.walls.down);
    // printf("lines = %d, columns = %d\n", i, j);
    // i = 0;
    // find_corners(cub3d.map_content, y[0] + 1, x[0], RIGHT);
    // return (0);
    // while (i < k)
    // {
    //     printf("(%d, %d)\n", x[i], y[i]);
    //     i++;
    // }
    return (0);
}
