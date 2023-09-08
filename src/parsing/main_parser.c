/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:16:25 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/08 20:12:42 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	map_path_is_valid(char *path)
{
	size_t	path_len;

	path_len = ft_strlen(path);
	if (path_len < 5)
		exit_cub3d(-1, "invalid file name");
	if (ft_strncmp(path + path_len - 4, ".cub", 4))
		exit_cub3d(-1, "invalid extension scheme");
}

static void	add_original_content_len(t_cub3d *cub3d, char *content)
{
	size_t	len;
	size_t	*temp;

	len = ft_strlen(content);
	temp = cub3d->content_len;
	cub3d->content_len = add_element_to_array(temp, &len, sizeof(size_t));
	if (!cub3d->content_len)
		exit_cub3d(ENOMEM, "couldn't malloc the content len");
	ft_free_node(1, temp);
}

static void	read_map(int map_file, t_cub3d *cub3d)
{
	char	*line;
	char	**prev_content;

	line = get_next_line(map_file);
	while (line)
	{
		add_original_content_len(cub3d, line);
		prev_content = cub3d->map_content;
		cub3d->map_content = add_element_to_array(prev_content, &line,
				sizeof(char *));
		if (!cub3d->map_content)
			exit_cub3d(ENOMEM, "couldn't malloc the map content");
		ft_free_node(1, prev_content);
		line = get_next_line(map_file);
	}
	if (!cub3d->map_content)
		exit_cub3d(-1, "empty map file");
}

void	cub3d_parser(int argc, char *argv[], t_cub3d *cub3d)
{
	int	map_file;

	if (argc != 2)
		exit_cub3d(-1, "only need the map file");
	map_path_is_valid(argv[1]);
	map_file = open(argv[1], O_RDONLY);
	if (map_file == -1)
		exit_cub3d(-1, "couldn't open the map file");
	read_map(map_file, cub3d);
	parse_textures(cub3d);
	skip_empty_lines(cub3d);
	if (!*cub3d->map_content)
		exit_cub3d(-1, "no map given");
	justify_lines(cub3d);
	map_parser(cub3d);
	skip_empty_lines(cub3d);
	if (!*cub3d->map_content)
		exit_cub3d(-1, "no map given");
}
