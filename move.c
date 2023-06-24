/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:57:07 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/24 10:59:41 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move(int keycode, t_cube *cube)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 2)
		cube->player.lor = -1;
	if (keycode == 0)
		cube->player.lor = 1;
	if (keycode == 13)
		cube->player.uod = -1;
	if (keycode == 1)
		cube->player.uod = 1;
	if (keycode == 123)
		cube->player.a = -1;
	if (keycode == 124)
		cube->player.a = 1;
	return (0);
}

int	no_move(int keycode, t_cube *cube)
{
	if (keycode == 2)
		cube->player.lor = 0;
	if (keycode == 0)
		cube->player.lor = 0;
	if (keycode == 13)
		cube->player.uod = 0;
	if (keycode == 1)
		cube->player.uod = 0;
	if (keycode == 124)
		cube->player.a = 0;
	if (keycode == 123)
		cube->player.a = 0;
	return (0);
}

int	update_player(t_cube *cube)
{
	if (cube->player.lor == -1)
		update_player_toward_right(cube);
	else if (cube->player.lor == 1)
		update_player_toward_left(cube);
	if (cube->player.uod == -1)
		update_player_forward(cube);
	else if (cube->player.uod == 1)
		update_player_backward(cube);
	if (cube->player.a == -1)
		cube->player.angle -= 0.01 * M_PI;
	else if (cube->player.a == 1)
		cube->player.angle += 0.01 * M_PI;
	if (cube->player.angle > 2 * M_PI)
		cube->player.angle -= 2 * M_PI;
	if (cube->player.angle < 0)
		cube->player.angle += 2 * M_PI;
	return (0);
}

int	rotation(int x, int y, t_cube *cube)
{
	static int	tmp;

	(void)y;
	if ((x > WIDTH / 2 && x < WIDTH && tmp == 0) || x > tmp)
	{
		cube->player.angle -= 0.03;
		tmp = x;
	}
	else if ((x < WIDTH / 2 && x > 0 && tmp == 0) || x < tmp)
	{
		cube->player.angle += 0.03;
		tmp = x;
	}
	if (tmp < 0)
		tmp++;
	if (tmp > WIDTH)
		tmp--;
	if (cube->player.angle > 2 * M_PI)
		cube->player.angle -= 2 * M_PI;
	if (cube->player.angle < 0)
		cube->player.angle += 2 * M_PI;
	return (1);
}
