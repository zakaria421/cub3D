/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:51:47 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/25 10:24:41 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_double_strlen(char **s)
{
	size_t	i;

	i = 0;
	while (s[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	ft_stlen_v2(char **str, int y)
{
	int	i;

	i = 0;
	while (str[y][i])
		i++;
	return (i);
}

float	calcul_c(int y, int c)
{
	float	i;

	i = 0;
	if (c < 0)
	c = 0;
	while  (y <= HIGHT / 2 + c / 2)
	{
		y++;
		i++;
	}
	return (i);
}

int	close_pro(t_cube *cube)
{
	mlx_destroy_window(cube->mlx.mlx_ptr, cube->mlx.win_ptr);
	exit(0);
}
