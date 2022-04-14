#include "fdf.h"

void	ft_mlx_pixel_put(t_map *m, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return ;
	dst = m->addr + (y * m->line_length + x * (m->bpp / 8));
	*(unsigned int *) dst = color;
}

static void	draw_line_util(int *d, int *s, int a, int b, int y)
{
	*d = abs(b - a);
	if (y)
		*d = -*d;
	if (a < b)
		*s = 1;
	else
		*s = -1;
}

void	draw_line(t_map *m, t_coord a, t_coord b, int color)
{
	t_coord	d;
	t_coord	s;
	int		err[2];

	draw_line_util(&d.x, &s.x, a.x, b.x, 0);
	draw_line_util(&d.y, &s.y, a.y, b.y, 1);
	err[0] = d.x + d.y;
	while (1)
	{
		ft_mlx_pixel_put(m, a.x, a.y, color);
		if (a.x == b.x && a.y == b.y)
			break ;
		err[1] = 2 * err[0];
		if (err[1] >= d.y)
		{
			if (a.x == b.x)
				break ;
			err[0] += d.y;
			a.x += s.x;
		}
		if (err[1] <= d.x)
		{
			if (a.y == b.y)
				break ;
			err[0] += d.x;
			a.y += s.y;
		}
	}
}

//   int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
//   int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
//   int err = (dx>dy ? dx : -dy)/2, e2;

//   for(;;){
//     ft_mlx_pixel_put(m, x0,y0, color);
//     if (x0==x1 && y0==y1) break;
//     e2 = err;
//     if (e2 >-dx) { err -= dy; x0 += sx; }
//     if (e2 < dy) { err += dx; y0 += sy; }
//   }

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
				draw_line(m,
					project(m, m->map[idx - 1]),
					project(m, m->map[idx]), color);
			if (i > 0)
				draw_line(m,
					project(m, m->map[idx - m->width]),
					project(m, m->map[idx]), color);
		}
	}
}

int	render_frame(t_map *m)
{
	int	i;
	int	*img;

	i = 0;
	img = (int *)m->addr;
	ft_bzero(m->addr, WIN_WIDTH * WIN_HEIGHT * (m->bpp / 8));
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
