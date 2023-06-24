/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:46:18 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/24 11:48:02 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_check(double angle, float *xstep, float *ystep)
{
	if (angle > 0 && angle < M_PI && *ystep < 0)
		*ystep *= -1;
	else if (angle < 2 * M_PI && angle > M_PI && *ystep > 0)
		*ystep *= -1;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2 && *xstep > 0)
		*xstep *= -1;
	else if (((angle < M_PI / 2 && angle < 0) || (angle > 3 * M_PI / 2
				&& angle < 2 * M_PI)) && *xstep < 0)
		*xstep *= -1;
}

t_hit	*hit_init(t_hit *hit, double angle)
{
	hit->angle = angle;
	hit->vertical = 0;
	return (hit);
}

t_hitfinder	y_and_ystep(t_cube *cube, t_hitfinder h, double angle)
{
	h.y = floor(cube->player.y / TOLE) * TOLE;
	h.ystep = TOLE;
	if (angle < M_PI && angle > 0)
		h.y += TOLE;
	else
		h.ystep = -TOLE;
	return (h);
}

t_hitfinder	x_and_xstep(t_cube *cube, t_hitfinder h, double angle)
{
	h.x = cube->player.x + ((h.y - cube->player.y) / tan(angle));
	h.xstep = TOLE / tan(angle);
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2 && h.xstep > 0)
		h.xstep *= -1;
	return (h);
}

t_hitfinder	finder_init(void)
{
	t_hitfinder	h;

	h.x = 0;
	h.y = 0;
	h.xstep = 0;
	h.ystep = 0;
	return (h);
}
