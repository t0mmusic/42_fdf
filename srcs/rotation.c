/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:16:17 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/29 22:16:27 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int theta, int **nodes)
{
	double	sin_theta;
	double	cos_theta;
	int		*node;
	int		z;
	int		y;
	int		i;

	sin_theta = sin(theta);
	cos_theta = cos(theta);
	i = 0;
	while (i < 8)
	{
		node = nodes[i];
		y = node[1];
		z = node[2];
		node[1] = ft_abs(y * cos_theta - z * sin_theta);
		node[2] = ft_abs(z * cos_theta + y * sin_theta);
		i++;
	}
}

void	rotate_y(int theta, int **nodes)
{
	double	sin_theta;
	double	cos_theta;
	int		*node;
	int		x;
	int		z;
	int		i;

	sin_theta = sin(theta);
	cos_theta = cos(theta);
	i = 0;
	while (i < 8)
	{
		node = nodes[i];
		x = node[0];
		z = node[2];
		node[0] = ft_abs(x * cos_theta + z * sin_theta);
		node[2] = ft_abs(z * cos_theta - x * sin_theta);
		i++;
	}
}

void	rotate_z(int theta, int **nodes)
{
	double	sin_theta;
	double	cos_theta;
	int		*node;
	int		x;
	int		y;
	int		i;

	sin_theta = sin(theta);
	cos_theta = cos(theta);
	i = 0;
	while (i < 8)
	{
		node = nodes[i];
		x = node[0];
		y = node[1];
		node[0] = ft_abs(x * cos_theta - y * sin_theta);
		node[1] = ft_abs(y * cos_theta + x * sin_theta);
		i++;
	}
}