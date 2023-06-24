/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:44:28 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/24 11:45:22 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vertical_hit(t_cube *cube,double angle,t_hit *hit)
{
	t_hitfinder h;
	
	h = finder_init();
	if (cube->map[(int)floor(cube->player.y / TOLE)][(int)floor(cube->player.x / TOLE)] == '1' || angle == 3 * M_PI / 2 || angle == M_PI / 2)
		return;
	h = x_and_xstep_vertical(cube,angle,h);
	h = y_and_ystep_vertical(cube,angle,h);
	if ((int)floor(h.y/TOLE) >= (int)ft_double_strlen(cube->map) || (int)floor(h.y/TOLE) < 0 || (int)floor(h.x/TOLE) >= (int)ft_stlen_v2(cube->map,(int)floor(h.y/TOLE)) || (int)floor(h.x/TOLE) < 0)
			return;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		h.x--;
	step_check(angle,&h.xstep,&h.ystep);
	while (cube->map[(int)floor(h.y / TOLE)] && cube->map[(int)floor(h.y / TOLE)][(int)floor(h.x / TOLE)] && cube->map[(int)floor(h.y / TOLE)][(int)floor(h.x / TOLE)] != '1')
	{
		h.y += h.ystep;
		h.x += h.xstep;
		if ((int)floor(h.y/TOLE) >= (int)ft_double_strlen(cube->map) || (int)floor(h.y/TOLE) < 0 || (int)floor(h.x/TOLE) >= (int)ft_stlen_v2(cube->map,(int)floor(h.y/TOLE)) || (int)floor(h.x/TOLE) < 0)
			return;
	}
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		h.x++;
	hit = distance_calcu(cube,hit,h);
}

void	horizintol_hit(t_cube *cube,double angle,t_hit *hit)
{
	t_hitfinder h;
	
	h = finder_init();
	hit = hit_init(hit,angle);
	if (angle == 0 || angle == M_PI || angle == 2 * M_PI)
		return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));
	h = y_and_ystep(cube,h,angle);
	h = x_and_xstep(cube,h,angle);
	if (angle > M_PI && angle < 2 * M_PI)
		h.y--;
	if ((int)floor(h.y/TOLE) > (int)ft_double_strlen(cube->map) || (int)floor(h.y/TOLE) < 0 || (int)floor(h.x/TOLE) > (int)ft_stlen_v2(cube->map,(int)floor(h.y/TOLE)) || (int)floor(h.x/TOLE) < 0)
		return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));	
	step_check(angle,&h.xstep,&h.ystep);
	while (cube->map[(int)floor(h.y / TOLE)] && cube->map[(int)floor(h.y / TOLE)][(int)floor(h.x / TOLE)] && cube->map[(int)floor(h.y / TOLE)][(int)floor(h.x / TOLE)] != '1')
	{
		h.y += h.ystep;
		h.x += h.xstep;
		if ((int)floor(h.y/TOLE) > (int)ft_double_strlen(cube->map) || (int)floor(h.y/TOLE) < 0 || (int)floor(h.x/TOLE) > (int)ft_stlen_v2(cube->map,(int)floor(h.y/TOLE)) || (int)floor(h.x/TOLE) < 0)
			return(hit->x = DBL_MAX, (void)(hit->y = DBL_MAX));
	}
	if (angle > M_PI && angle < 2 * M_PI)
		h.y++;
	hit->x = h.x;
	hit->y = h.y;
}
