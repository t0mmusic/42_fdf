/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:36:24 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/30 17:36:49 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

void	plot_point(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->ll + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

void highest_common_factor(int *a, int *b)
{
	int	factor;

	if (!*a || !*b)
		return ;
	if (*a == *b)
	{
		*a /= *a;
		*b /= *b;
		return ;
	}
	if (*a < *b)
		factor = *a;
	else
		factor = *b;
	*a /= factor;
	*b /= factor;
}

void	draw_box(t_mlx *mlx, int **nodes)
{
	draw_line(mlx, nodes[0][0], nodes[0][1], nodes[2][0], nodes[2][1]);
	draw_line(mlx, nodes[0][0], nodes[0][1], nodes[4][0], nodes[4][1]);
	draw_line(mlx, nodes[4][0], nodes[4][1], nodes[6][0], nodes[6][1]);
	draw_line(mlx, nodes[2][0], nodes[2][1], nodes[6][0], nodes[6][1]);

	draw_line(mlx, nodes[1][0], nodes[1][1], nodes[5][0], nodes[5][1]);
	draw_line(mlx, nodes[1][0], nodes[1][1], nodes[3][0], nodes[3][1]);
	draw_line(mlx, nodes[3][0], nodes[3][1], nodes[7][0], nodes[7][1]);
	draw_line(mlx, nodes[5][0], nodes[5][1], nodes[7][0], nodes[7][1]);

	draw_line(mlx, nodes[0][0], nodes[0][1], nodes[1][0], nodes[1][1]);
	draw_line(mlx, nodes[2][0], nodes[2][1], nodes[3][0], nodes[3][1]);
	draw_line(mlx, nodes[4][0], nodes[4][1], nodes[5][0], nodes[5][1]);
	draw_line(mlx, nodes[6][0], nodes[6][1], nodes[7][0], nodes[7][1]);
}

void	draw_helper(t_mlx *mlx, int col)
{
	int		x;
	int		y;

	y = 20;
	x = 500;
	mlx_string_put(mlx->mlx, mlx->win, x - 20, y, col, "Usage");
	mlx_string_put(mlx->mlx, mlx->win, x, y + 30, col, "Disable usage   space");
	mlx_string_put(mlx->mlx, mlx->win, x, y + 55, col, "Move            < ^ v >");
	mlx_string_put(mlx->mlx, mlx->win, x, y + 80, col, "Move            q w a d");
	mlx_string_put(mlx->mlx, mlx->win, x, y + 105, col, "Zoom            + -");
	mlx_string_put(mlx->mlx, mlx->win, x, y + 130, col, "Scale up        page up");
	mlx_string_put(mlx->mlx, mlx->win, x, y + 155, col, "Scale down      page down");
	mlx_string_put(mlx->mlx, mlx->win, x, y + 180, col, "Angle           q e");
	mlx_string_put(mlx->mlx, mlx->win, x, y + 205, col, "Projection      p");
	mlx_string_put(mlx->mlx, mlx->win, x, y + 230, col, "Colortheme      c");
}

void	clear_image(t_mlx *mlx)
{
	int x;
	int y;
	int	x_max;
	int	y_max;

	x = 0;
	mlx_get_screen_size(mlx->mlx, &x_max, &y_max);
	while (x < x_max)
	{
		y = 0;
		while (y < y_max)
		{
			plot_point(mlx, x, y, 0x00000000);
			++y;
		}
		++x;
	}
}

int	key_press(int key, void *data)
{
	t_mlx	*mlx;

	mlx = data;
	ft_printf("%i\n", key);
	if (key == UP)
	{
		rotate(mlx, 5, 0);
		rotate_x(5, mlx->nodes);
	}
	if (key == DOWN)
	{
		rotate(mlx, -5, 0);
		rotate_x(-5, mlx->nodes);
	}
	if (key == LEFT)
	{
		rotate(mlx, 5, 1);
		rotate_y(5, mlx->nodes);
	}
	if (key == RIGHT)
	{
		rotate(mlx, -5, 1);
		rotate_y(-5, mlx->nodes);
	}
	if (key == ESCAPE)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit (0);
	}
	mlx_clear_window(mlx->mlx, mlx->win);
	clear_image(mlx);
	draw_helper(mlx, 0x00FF0000);
	draw_map(mlx);
	draw_box(mlx, mlx->nodes);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (key);
}

void	ft_mlx_loop(t_mlx *mlx, int **nodes)
{
	mlx->nodes = nodes;
	mlx_key_hook(mlx->win, key_press, mlx);
	mlx_loop(mlx->mlx);
}

void	draw_points(t_mlx *mlx)
{
	int node0[] = {500, 500, 500};
	int node1[] = {500, 500, 700};
	int node2[] = {500, 700, 500};
	int node3[] = {500, 700, 700};
	int node4[] = {700, 500, 500};
	int node5[] = {700, 500, 700};
	int node6[] = {700, 700, 500};
	int node7[] = {700, 700, 700};
	int *nodes[] = {node0, node1, node2, node3, node4, node5, node6, node7};
	ft_mlx_loop(mlx, nodes);
}

int main(int ac, char **av)
{
    t_mlx   mlx;

	if (ac != 2)
	{
		ft_printf("Map Please!\n");
		return (1);
	}
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "Hello world!");
	mlx.img = mlx_new_image(mlx.mlx, 1920, 1080);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.ll,
								&mlx.endian);
	import_map(av[1], &mlx);
	draw_points(&mlx);
}