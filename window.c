/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:00:44 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/24 17:24:01 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(t_cube *cube, int x, int y)
{
	while (y < (int)ft_double_strlen(cube->map))
	{
		x = 0;
		while (x < (int)ft_strlen(cube->map[y]))
		{
			x++;
			if (cube->map[y][x] == 'N' || cube->map[y][x] == 'S'
				|| cube->map[y][x] == 'E' || cube->map[y][x] == 'W')
			{
				cube->player.x = x * TOLE + TOLE / 2;
				cube->player.y = y * TOLE + TOLE / 2;
				if (cube->map[y][x] == 'N')
					cube->player.angle = 3 * M_PI / 2;
				else if (cube->map[y][x] == 'S')
					cube->player.angle = M_PI / 2;
				else if (cube->map[y][x] == 'E')
					cube->player.angle = 0;
				else if (cube->map[y][x] == 'W')
					cube->player.angle = M_PI;
				return ;
			}
		}
		y++;
	}
}

void	draw_all(t_cube *cube, int y)
{
	t_hit	x;
	double	angle;
	int		i;

	i = 0;
	angle = cube->player.angle - 30 * M_PI / 180;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	while (i < WIDTH)
	{
		horizintol_hit(cube, angle, &x);
		vertical_hit(cube, angle, &x);
		d_game(cube, sqrt(pow(x.x - cube->player.x, 2) + pow(x.y
					- cube->player.y, 2)) * cos(angle - cube->player.angle),
			y, x);
		y++;
		i++;
		angle += (60 * M_PI / 180) / (WIDTH);
		if (angle > 2 * M_PI)
			angle -= 2 * M_PI;
		if (angle < 0)
			angle += 2 * M_PI;
	}
}

int	update(t_cube *cube)
{
	mlx_clear_window(cube->mlx.mlx_ptr, cube->mlx.win_ptr);
	cube->mlx.img = mlx_new_image(cube->mlx.mlx_ptr, WIDTH, HIGHT);
	cube->mlx.data = mlx_get_data_addr(cube->mlx.img, &cube->mlx.bits_per_pixel,
			&cube->mlx.line_length, &cube->mlx.endian);
	update_player(cube);
	draw_all(cube, 0);
	mlx_put_image_to_window(cube->mlx.mlx_ptr, cube->mlx.win_ptr, cube->mlx.img,
		0, 0);
	mlx_destroy_image(cube->mlx.mlx_ptr, cube->mlx.img);
	return (0);
}

void	start(t_map *g)
{
	t_cube	cube;

	cube.ea = g->ea;
	cube.we = g->we;
	cube.so = g->so;
	cube.no = g->no;
	cube.player.a = 0;
	cube.player.lor = 0;
	cube.player.uod = 0;
	cube.map = g->map;
	cube.fc = g->f;
	cube.cc = g->c;
	find_player(&cube, 0, 0);
	cube.mlx.mlx_ptr = mlx_init();
	cube.mlx.win_ptr = mlx_new_window(cube.mlx.mlx_ptr, WIDTH, HIGHT, "cub3d");
	texture(&cube);
	mlx_hook(cube.mlx.win_ptr, 17, 0, close_pro, &cube);
	mlx_hook(cube.mlx.win_ptr, 2, 0, move, &cube);
	mlx_hook(cube.mlx.win_ptr, 6, 0, rotation, &cube);
	mlx_hook(cube.mlx.win_ptr, 3, 0, no_move, &cube);
	mlx_loop_hook(cube.mlx.mlx_ptr, update, &cube);
	mlx_loop(cube.mlx.mlx_ptr);
}
