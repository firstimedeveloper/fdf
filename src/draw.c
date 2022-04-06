#include "fdf.h"

void	ft_mlx_pixel_put(t_map *m, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return ;
	dst = m->addr + (y * m->line_length + x * (m->bpp / 8));
	*(unsigned int*)dst = color;
}

void draw_line(t_map *m, t_coord a, t_coord b, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(b.x - a.x);
	dy = -abs(b.y - a.y);
	if (a.x < b.x)
		sx = 1;
	else
		sx = -1;
	if (a.y < b.y)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (1)
	{
		ft_mlx_pixel_put(m, a.x, a.y, color);
		if (a.x == b.x && a.y == b.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			if (a.x == b.x)
				break ;
			err += dy;
			a.x += sx;
		}
		if (e2 <= dx)
		{
			if (a.y == b.y)
				break ;
			err += dx;
			a.y += sy;
		}
	}

//   int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
//   int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
//   int err = (dx>dy ? dx : -dy)/2, e2;

//   for(;;){
//     ft_mlx_pixel_put(m, x0,y0, color);   //color the pixel in the matrix for later use.
//     if (x0==x1 && y0==y1) break;
//     e2 = err;
//     if (e2 >-dx) { err -= dy; x0 += sx; }
//     if (e2 < dy) { err += dx; y0 += sy; }
//   }
}

// void	draw_line(t_map *m, int a, int b, int c, int d, color)
// {
// 	int	dx;
// 	int	dy;
// 	int	D;
// 	int	x;
// 	int	y;

// 	dx = c - a;
// 	dy = d - b;
// 	D = 2 * dy - dx;
// 	x = a;
// 	y = b;
// 	while (x <= c)
// 	{
// 		ft_mlx_pixel_put(m, x, y, color);
// 		if (D > 0)
// 		{
// 			y++;
// 			D = D - 2 * dx;
// 		}
// 		D = D + 2 * dy;
// 		x++;
// 	}

// }
#include <stdio.h>
void	draw_map(t_map *m, int color)
{
	int	i;
	int	j;
	int	idx;

	i = -1;
	while (++i < m->height)
	{
		j = -1;
		while (++j < m->width)
		{
			idx = i * m->width + j;
			if (j > 0)
				draw_line(m, project(m, m->map[idx - 1]), project(m, m->map[idx]), color);
			if (i > 0)
				draw_line(m, project(m, m->map[idx - m->width]), project(m, m->map[idx]), color);
		}
	}
}

int	render_frame(t_map *m)
{
	ft_bzero(m->addr, WIN_WIDTH * WIN_HEIGHT * (m->bpp / 8));
	int i = 0;
	int *img;

	img = (int *)m->addr;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		img[i] = 0x202020;
		i++;
	}
	draw_map(m, 0x808080);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	return (0);
}

void	draw(t_map *m)
{
	init_map(m);
	render_frame(m);
}
