/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:00:19 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/25 14:36:28 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_toward_left(t_cube *cube)
{
	cube->player.x += 25 * cos(cube->player.angle - (M_PI / 2));
	cube->player.y += 25 * sin(cube->player.angle - (M_PI / 2));
	if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x)
			/ TOLE)] && (cube->map[(int)((cube->player.y)
				/ TOLE)][(int)((cube->player.x) / TOLE)] == '1'
			|| wall_check_test(cube) == 1))
	{
		cube->player.x -= 25 * cos(cube->player.angle - (M_PI / 2));
		cube->player.y -= 25 * sin(cube->player.angle - (M_PI / 2));
	}
	else
	{
		cube->player.x -= 20 * cos(cube->player.angle - (M_PI / 2));
		cube->player.y -= 20 * sin(cube->player.angle - (M_PI / 2));
	}
	return ;
}

void	update_player_toward_right(t_cube *cube)
{
	cube->player.x += 25 * cos(cube->player.angle + (M_PI / 2));
	cube->player.y += 25 * sin(cube->player.angle + (M_PI / 2));
	if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x)
			/ TOLE)] && (cube->map[(int)((cube->player.y)
				/ TOLE)][(int)((cube->player.x) / TOLE)] == '1'
			|| wall_check_test(cube) == 1))
	{
		cube->player.x -= 25 * cos(cube->player.angle + (M_PI / 2));
		cube->player.y -= 25 * sin(cube->player.angle + (M_PI / 2));
	}
	else
	{
		cube->player.x -= 20 * cos(cube->player.angle + (M_PI / 2));
		cube->player.y -= 20 * sin(cube->player.angle + (M_PI / 2));
	}
	return ;
}

void	update_player_forward(t_cube *cube)
{
	cube->player.x += 25 * cos(cube->player.angle);
	if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x)
			/ TOLE)] && (cube->map[(int)((cube->player.y)
				/ TOLE)][(int)((cube->player.x) / TOLE)] == '1'
			|| wall_check_test(cube) == 1))
		cube->player.x -= 25 * cos(cube->player.angle);
	else
		cube->player.x -= 20 * cos(cube->player.angle);
	cube->player.y += 25 * sin(cube->player.angle);
	if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x)
			/ TOLE)] && (cube->map[(int)((cube->player.y)
				/ TOLE)][(int)((cube->player.x) / TOLE)] == '1'
			|| wall_check_test(cube) == 1))
		cube->player.y -= 25 * sin(cube->player.angle);
	else
		cube->player.y -= 20 * sin(cube->player.angle);
	return ;
}

void	update_player_backward(t_cube *cube)
{
	cube->player.x -= 25 * cos(cube->player.angle);
	if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x)
			/ TOLE)] && (cube->map[(int)((cube->player.y)
				/ TOLE)][(int)((cube->player.x) / TOLE)] == '1'
			|| wall_check_test(cube) == 1))
		cube->player.x += 25 * cos(cube->player.angle);
	else
		cube->player.x += 20 * cos(cube->player.angle);
	cube->player.y -= 25 * sin(cube->player.angle);
	if (cube->map[(int)((cube->player.y) / TOLE)][(int)((cube->player.x)
			/ TOLE)] && (cube->map[(int)((cube->player.y)
				/ TOLE)][(int)((cube->player.x) / TOLE)] == '1'
			|| wall_check_test(cube) == 1))
		cube->player.y += 25 * sin(cube->player.angle);
	else
		cube->player.y += 20 * sin(cube->player.angle);
	return ;
}

int	wall_check_test(t_cube *cube)
{
	if (cube->map[(int)((cube->player.y + 10) / TOLE)][(int)((cube->player.x)
			/ TOLE)] == '1' && cube->map[(int)((cube->player.y)
			/ TOLE)][(int)((cube->player.x + 10) / TOLE)] == '1')
		return (1);
	if (cube->map[(int)((cube->player.y + 10) / TOLE)][(int)((cube->player.x)
			/ TOLE)] == '1' && cube->map[(int)((cube->player.y)
			/ TOLE)][(int)((cube->player.x - 10) / TOLE)] == '1')
		return (1);
	if (cube->map[(int)((cube->player.y - 10) / TOLE)][(int)((cube->player.x)
			/ TOLE)] == '1' && cube->map[(int)((cube->player.y)
			/ TOLE)][(int)((cube->player.x + 10) / TOLE)] == '1')
		return (1);
	if (cube->map[(int)((cube->player.y - 10) / TOLE)][(int)((cube->player.x)
			/ TOLE)] == '1' && cube->map[(int)((cube->player.y)
			/ TOLE)][(int)((cube->player.x - 10) / TOLE)] == '1')
		return (1);
	return (0);
}
