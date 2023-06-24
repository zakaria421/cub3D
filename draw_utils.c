/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:25:48 by zbentalh          #+#    #+#             */
/*   Updated: 2023/06/24 17:25:39 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture(t_cube *cube)
{
	cube->text[0].img = mlx_xpm_file_to_image(cube->mlx.mlx_ptr, cube->we,
			&cube->text[0].width, &cube->text[0].hight);
	cube->text[1].img = mlx_xpm_file_to_image(cube->mlx.mlx_ptr, cube->ea,
			&cube->text[1].width, &cube->text[1].hight);
	cube->text[2].img = mlx_xpm_file_to_image(cube->mlx.mlx_ptr, cube->no,
			&cube->text[2].width, &cube->text[2].hight);
	cube->text[3].img = mlx_xpm_file_to_image(cube->mlx.mlx_ptr, cube->so,
			&cube->text[3].width, &cube->text[3].hight);
	if (cube->text[0].img == NULL || cube->text[1].img == NULL
		|| cube->text[2].img == NULL || cube->text[3].img == NULL)
		(write(2, "Error: a texture is not valide \n", 33), exit(1));
	cube->text[0].data = mlx_get_data_addr(cube->text[0].img,
			&cube->text[0].bits_per_pixel, &cube->text[0].line_length,
			&cube->text[0].endian);
	cube->text[1].data = mlx_get_data_addr(cube->text[1].img,
			&cube->text[1].bits_per_pixel, &cube->text[1].line_length,
			&cube->text[1].endian);
	cube->text[2].data = mlx_get_data_addr(cube->text[2].img,
			&cube->text[2].bits_per_pixel, &cube->text[2].line_length,
			&cube->text[2].endian);
	cube->text[3].data = mlx_get_data_addr(cube->text[3].img,
			&cube->text[3].bits_per_pixel, &cube->text[3].line_length,
			&cube->text[3].endian);
	return ;
}

int	texture_color(t_cube *cube, int x, int y, int i)
{
	char	*dst;
	int		color;

	if (x < 0 || y < 0 || x >= cube->text[i].width || y >= cube->text[i].hight)
		return (0);
	dst = cube->text[i].data + (y * cube->text[i].line_length + x
			* (cube->text[i].bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	my_mlx_pixel_put(t_cube *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HIGHT)
		return ;
	dst = data->mlx.data + (y * data->mlx.line_length + x
			* (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_vertical_wall(t_cube *cube, int tmp_x, t_hit hit, t_draw draw)
{
	if (hit.angle > M_PI / 2 && hit.angle < 3 * M_PI / 2)
		my_mlx_pixel_put(cube, tmp_x, draw.y, texture_color(cube, draw.r,
				(int)draw.l, 0));
	else
		my_mlx_pixel_put(cube, tmp_x, draw.y, texture_color(cube, draw.r,
				(int)draw.l, 1));
}
