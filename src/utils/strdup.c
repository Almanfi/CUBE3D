/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:09:17 by bamrouch          #+#    #+#             */
/*   Updated: 2023/07/02 14:35:39 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*pro_strdup(char *str)
{
	char	*res;
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen(str);
	res = ft_malloc((str_len + 1) * sizeof(char), (t_mem_param){NULL, 1, NULL,
			0});
	if (!res)
		return (NULL);
	i = 0;
	while (*(str + i))
	{
		*(res + i) = *(str + i);
		i++;
	}
	*(res + i) = 0;
	return (res);
}
