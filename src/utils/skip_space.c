/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:14:37 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/02 20:11:48 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_boolean	ft_is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f' || c == '\n')
        return TRUE;
    return FALSE;
}

char	*skip_space(char *str)
{
    if (!str)
        return str;
    while (*str && ft_is_space(*str))
		str++;
    // printf("skip space after |%s|\n", str);
	return str;
}
