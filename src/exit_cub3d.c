/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulkh <maboulkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:45:13 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/06 18:08:06 by maboulkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_cub3d(int err_code, char *message)
{
	t_cub3d	*cub3d;

	cub3d = get_cub3d(NULL);
	if (err_code >= 0)
		ft_putstr_fd(strerror(err_code), STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
	if (cub3d->imgs)
		while (*cub3d->imgs)
			mlx_destroy_image(cub3d->mlx, *(cub3d->imgs++));
	ft_free(0, TRUE);
	exit(1);
}
