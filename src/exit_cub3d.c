/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:45:13 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/02 14:37:46 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void    exit_cub3d(int  err_code, char *message)
{
    if (err_code >= 0)
        ft_putstr_fd(strerror(err_code), STDERR_FILENO);
    if (message)
        ft_putstr_fd(message, STDERR_FILENO);
    ft_putendl_fd("", STDERR_FILENO);
    ft_free(0, TRUE);
    exit(1);
}
