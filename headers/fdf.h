/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:37:22 by jbrown            #+#    #+#             */
/*   Updated: 2022/07/30 17:35:42 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "ft_printf.h"
# include "mlx.h"
# include "get_next_line_bonus.h"
# include <fcntl.h>
# include <math.h>

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ESCAPE 65307

typedef struct s_node
{
    int x;
    int y;
    int z;
}   t_node;

typedef struct s_mlx
{
    t_node  **points;
    int     **map;
    int     max_x;
    int     max_y;
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     ll;
    int     endian;
    int     **nodes;
}   t_mlx;

void    import_map(char *map, t_mlx *mlx);

void	plot_point(t_mlx *mlx, int x, int y, int color);
void	draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1);
void    draw_map(t_mlx *mlx);

void	rotate_x(int theta, int **nodes);
void	rotate_y(int theta, int **nodes);
void	rotate_z(int theta, int **nodes);

void	rot_x(int theta, t_mlx *mlx, int x, int y);
void	rot_y(int theta, t_mlx *mlx, int x, int y);
void	rot_z(int theta, t_mlx *mlx, int x, int y);
void	rotate(t_mlx *mlx, int theta, int axis);

int	    ft_abs(int num);

void    free_arrayp(char **arr);
void    free_list(t_list *lst);

#endif