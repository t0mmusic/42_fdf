/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:37:44 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/31 12:39:35 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    print_map(t_mlx *mlx)
{
	int x;
	int y;

	y = 0;
	while (y < mlx->max_y)
	{
		x = 0;
		while (x < mlx->max_x)
		{
			ft_printf("x: %i y: %i z: %i | ", mlx->points[y][x].x, mlx->points[y][x].y, mlx->points[y][x].z);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

int x_size(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

t_node *array_to_node(char **arr, int y)
{
	int 	i;
	t_node	*node;

	node = malloc(sizeof(*node) * x_size(arr));
	i = 0;
	while (arr[i] && ft_strcmp(arr[i], "\n"))
	{
		node[i].z = ft_atoi(arr[i]);
		node[i].x = i;
		node[i].y = y;
		i++;
	}
	return (node);
}

void    map_to_int(t_list *map_list, t_mlx *mlx)
{
	char    **tmp;
	int     i;

	mlx->max_y = ft_lstsize(map_list) - 1;
	mlx->max_x = x_size(map_list->content) - 1;
	mlx->points = malloc(sizeof(*mlx->points) * mlx->max_y);
	i = 0;
	while (map_list->next)
	{
		tmp = ft_split(map_list->content, ' ');
		mlx->points[i] = array_to_node(tmp, i);
		i++;
		map_list = map_list->next;
	}
	mlx->max_x = x_size(tmp) - 1;
	print_map(mlx);
}

void    import_map(char *map, t_mlx *mlx)
{
	int		fd;
	t_list	*map_list;
	char	*line;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	map_list = ft_lstnew(line);
	while (line)
	{
		line = get_next_line(fd);
		ft_lstadd_back(&map_list, ft_lstnew(line));
	}
	map_to_int(map_list, mlx);
	free_list(map_list);
}