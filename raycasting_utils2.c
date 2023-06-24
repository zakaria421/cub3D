/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:48:23 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/24 17:30:13 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_hitfinder	x_and_xstep_vertical(t_cube *cube, double angle, t_hitfinder h)
{
	h.x = floor(cube->player.x / TOLE) * TOLE;
	h.xstep = TOLE;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		h.xstep = -TOLE;
	else
		h.x += TOLE;
	return (h);
}

t_hitfinder	y_and_ystep_vertical(t_cube *cube, double angle, t_hitfinder h)
{
	h.y = cube->player.y + ((h.x - cube->player.x) * tan(angle));
	h.ystep = TOLE * tan(angle);
	if (angle > M_PI && angle < 2 * M_PI && h.ystep > 0)
		h.ystep *= -1;
	return (h);
}

t_hit	*distance_calcu(t_cube *cube, t_hit *hit, t_hitfinder h)
{
	if (sqrt(pow(hit->x - cube->player.x, 2) + pow(hit->y - cube->player.y,
				2)) > sqrt(pow(h.x - cube->player.x, 2) + pow(h.y
				- cube->player.y, 2)))
	{
		hit->x = h.x;
		hit->y = h.y;
		hit->vertical = 1;
	}
	return (hit);
}

int	vertical_see(t_cube *cube, double angle)
{
	if (cube->map[(int)floor(cube->player.y / TOLE)][(int)floor(cube->player.x
			/ TOLE)] == '1' || angle == 3 * M_PI / 2 || angle == M_PI / 2)
		return (1);
	return (0);
}
