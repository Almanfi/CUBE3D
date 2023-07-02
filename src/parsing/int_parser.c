/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:22:15 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/02 14:22:42 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_boolean	ft_str_is_integer(const char *str, int *res)
{
	int		i;
	long	temp;
	long	is_neg;

	is_neg = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_neg = -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (FALSE);
	while (*str == '0')
		str++;
	i = 0;
	while (str[i])
		if (i > 10 || !ft_isdigit(str[i++]))
			return (FALSE);
	temp = ft_atoi(str) * is_neg;
	if (temp > INT_MAX || temp < INT_MIN)
		return (FALSE);
	*res = (int)temp;
	return (TRUE);
}
