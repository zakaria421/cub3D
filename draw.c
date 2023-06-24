/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:12:32 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/24 17:33:58 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_down(t_cube *cube, int y, int tmp_x)
{
	while (y < HIGHT)
	{
		my_mlx_pixel_put(cube, tmp_x, y, cube->cc);
		y++;
	}
}

void	draw_up(t_cube *cube, int y, int tmp_x)
{
	while (y > 0)
	{
		my_mlx_pixel_put(cube, tmp_x, y, cube->fc);
		y--;
	}
}

t_draw	draw_init(int c, t_hit hit)
{
	t_draw	draw;

	draw.y = HIGHT / 2 - c / 2;
	draw.i = (float)(TOLE / calcul_c(draw.y, c));
	draw.z = (hit.x / TOLE - (int)(hit.x / TOLE)) * TOLE;
	draw.r = (hit.y / TOLE - (int)(hit.y / TOLE)) * TOLE;
	draw.l = 0;
	return (draw);
}

void	draw_wall(t_cube *cube, int c, int tmp_x, t_hit hit)
{
	t_draw	draw;

	draw = draw_init(c, hit);
	while (draw.y < HIGHT && draw.y <= HIGHT / 2 + c / 2)
	{
		if (hit.vertical == 1)
			draw_vertical_wall(cube, tmp_x, hit, draw);
		else
		{
			if (hit.angle > 0 && hit.angle < M_PI)
				my_mlx_pixel_put(cube, tmp_x, draw.y, texture_color(cube,
						draw.z, (int)draw.l, 2));
			else
				my_mlx_pixel_put(cube, tmp_x, draw.y, texture_color(cube,
						draw.z, (int)draw.l, 3));
		}
		draw.y++;
		draw.l += draw.i;
	}
	draw_up(cube, HIGHT / 2 - c / 2, tmp_x);
	draw_down(cube, HIGHT / 2 + c / 2, tmp_x);
}

void	d_game(t_cube *cube, float i, int x, t_hit hit)
{
	double	c;
	float	tmp_x;

	tmp_x = (float)TOLE / i;
	c = tmp_x * ((WIDTH / 2) / tan(30 * M_PI / 180));
	if (c > 6000)
		c = 6000;
	draw_wall(cube, c, x, hit);
}
