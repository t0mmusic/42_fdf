/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 21:37:18 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/30 14:55:08 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	up_or_down(int *current, int end)
{
	if (end < *current)
		*current -= 1;
	else if (end > *current)
		*current += 1;
}

void	gentle_slope(t_mlx *mlx, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	d;
	int	x;
	int	y;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dy < 0)
		dy = -dy;
	d = (2 * dy) - dx;
	y = y0;
	x = x0;
	while (x != x1)
	{
		plot_point(mlx, x, y, 0x00FF0000);
		if (d > 0)
		{
			up_or_down(&y, y1);
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
		up_or_down(&x, x1);
	}
	plot_point(mlx, x, y, 0x00FF0000);
}

void    steep_slope(t_mlx *mlx, int x0, int y0, int x1, int y1)
{
	int dx;
	int dy;
	int d;
	int x;
	int y;

	dx = x1 - x0;
	dy = y1 - y0;
	if (dx < 0)
		dx = -dx;
	d = (2 * dx) - dy;
	x = x0;
	y = y0;
	while (y != y1)
	{
		plot_point(mlx, x, y, 0x00FF0000);
		if (d > 0)
		{
			up_or_down(&x, x1);
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
		up_or_down(&y, y1);
	}
	plot_point(mlx, x, y, 0x00FF0000);
}

void	draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1)
{
	if (ft_abs(y1 - y0) < ft_abs(x1 - x0))
	{
		if (x0 > x1)
			gentle_slope(mlx, x1, y1, x0, y0);
		else
			gentle_slope(mlx, x0, y0, x1, y1);
	}
	else
	{
		if (y0 > y1)
			steep_slope(mlx, x1, y1, x0, y0);
		else
			steep_slope(mlx, x0, y0, x1, y1);
	}
}