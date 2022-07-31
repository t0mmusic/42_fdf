/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:32:04 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/31 13:10:55 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rot_x(int theta, t_mlx *mlx, int x, int y)
{
	double	sin_theta;
	double	cos_theta;
	t_node	node;
	int		tmp_y;
	int		tmp_z;

	sin_theta = sin(theta);
	cos_theta = cos(theta);
	while (y < mlx->max_y)
	{
		x = 0;
		while (x < mlx->max_x)
		{
			node = mlx->points[y][x];
			tmp_y = node.y;
			tmp_z = node.z;
			node.y = ft_abs(tmp_y * cos_theta - tmp_z * sin_theta);
			node.z = ft_abs(tmp_z * cos_theta + tmp_y * sin_theta);
			// ft_printf("oldx: %i\nnewx: %i\noldy: %i\nnewy: %i\n\n", tmp_y, node.y, tmp_z, node.z);
			mlx->points[y][x] = node;
			x++;
		}
		y++;
	}
}

void	rot_y(int theta, t_mlx *mlx, int x, int y)
{
	double	sin_theta;
	double	cos_theta;
	t_node	node;
	int		tmp_x;
	int		tmp_z;

	sin_theta = sin(theta);
	cos_theta = cos(theta);
	while (y < mlx->max_y)
	{
		x = 0;
		while (x < mlx->max_x)
		{
			node = mlx->points[y][x];
			tmp_x = node.x;
			tmp_z = node.z;
			node.z = ft_abs(tmp_z * cos_theta - tmp_x * sin_theta);
			node.x = ft_abs(tmp_x * cos_theta + tmp_z * sin_theta);
			// ft_printf("oldx: %i\nnewx: %i\noldy: %i\nnewy: %i\n\n", tmp_x, node.x, tmp_z, node.z);
			mlx->points[y][x] = node;
			x++;
		}
		y++;
	}
}

void	rot_z(int theta, t_mlx *mlx, int x, int y)
{
	double	sin_theta;
	double	cos_theta;
	t_node	node;
	int		tmp_x;
	int		tmp_y;

	sin_theta = sin(theta);
	cos_theta = cos(theta);
	while (y < mlx->max_y)
	{
		x = 0;
		while (x < mlx->max_x)
		{
			node = mlx->points[y][x];
			tmp_x = node.x;
			tmp_y = node.y;
			node.x = ft_abs(tmp_x * cos_theta - tmp_y * sin_theta);
			node.y = ft_abs(tmp_y * cos_theta + tmp_x * sin_theta);
			mlx->points[y][x] = node;
			x++;
		}
		y++;
	}
}

void	iso(t_mlx *mlx)
{
	int	x;
	int	y;
	int	tmp_x;
	int	tmp_y;

	y = 0;
	while (y < mlx->max_y)
	{
		x = 0;
		while (x < mlx->max_x)
		{
			tmp_x = mlx->points[y][x].x;
			tmp_y = mlx->points[y][x].y;
			mlx->points[y][x].x = (tmp_x - tmp_y) * cos(0.523599);
			mlx->points[y][x].y = -(mlx->points[y][x].z) + (tmp_x + tmp_y) * sin(0.523599);
			x++;
		}
		y++;
	}
}

void	rotate(t_mlx *mlx, int theta, int axis)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (axis == 0)
	{
		rot_x(theta, mlx, x, y);
	}
	if (axis == 1)
	{
		rot_y(theta, mlx, x, y);
	}
	if (axis == 2)
	{
		rot_z(theta, mlx, x, y);
	}
}

void    draw_map(t_mlx *mlx)
{
	int x;
	int y;
	int x_offset;
	int y_offset;
	int	scale;

	y_offset = 300;
	x_offset = 500;
	scale = 40;
	y = 0;
	while (y < mlx->max_y)
	{
		x = 0;
		while (x < mlx->max_x + 1)
		{
			ft_printf("x%i: %i, y%i: %i\n", x, mlx->points[y][x].x, y, mlx->points[y][x].y);
			if (x < mlx->max_x)
			{
				// ft_printf("x0: %i\ny0: %i\nx1: %i\ny1: %i\n\n",
				// 	mlx->points[y][x].x * scale + x_offset, mlx->points[y][x].y * scale + y_offset,
				// 	mlx->points[y][x + 1].x * scale + x_offset, mlx->points[y][x].y * scale + y_offset);
				draw_line(mlx, mlx->points[y][x].x * scale + x_offset, mlx->points[y][x].y * scale + y_offset,
					mlx->points[y][x + 1].x * scale + x_offset, mlx->points[y][x].y * scale + y_offset);
			}
			if (y < mlx->max_y - 1)
			{
				draw_line(mlx, mlx->points[y][x].x * scale + x_offset, mlx->points[y][x].y * scale + y_offset,
					mlx->points[y][x].x * scale + x_offset, mlx->points[y + 1][x].y * scale + y_offset);
			}
			x++;
		}
		y++;
	}
}