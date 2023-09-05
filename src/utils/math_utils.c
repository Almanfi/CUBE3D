/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:26:24 by bamrouch          #+#    #+#             */
/*   Updated: 2023/09/05 16:39:40 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define PI 3.141592653589793

double	ft_abs(double value)
{
	if (value >= 0)
		return (value);
	return (-value);
}

double	degree_to_rad(double degree)
{
	return (degree * PI / 180.0);
}
