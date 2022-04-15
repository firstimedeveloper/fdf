/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:14:12 by juhan             #+#    #+#             */
/*   Updated: 2022/04/15 17:10:49 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_mlx_pixel_put(t_map *m, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return ;
	dst = m->addr + (y * m->line_length + x * (m->bpp / 8));
	*(unsigned int *) dst = color;
}

static void	draw_line_util(t_coord *d, t_coord *s, t_coord a, t_coord b)
{
	d->x = abs(b.x - a.x);
	d->y = -abs(b.y - a.y);
	if (a.x < b.x)
		s->x = 1;
	else
		s->x = -1;
	if (a.y < b.y)
		s->y = 1;
	else
		s->y = -1;
}

void	draw_line(t_map *m, t_coord a, t_coord b, int color)
{
	t_coord	d;
	t_coord	s;
	int		err[2];

	draw_line_util(&d, &s, a, b);
	err[0] = d.x + d.y;
	while (a.x != b.x || a.y != b.y)
	{
		ft_mlx_pixel_put(m, a.x, a.y, color);
		if (a.x == b.x && a.y == b.y)
			break ;
		err[1] = 2 * err[0];
		if (err[1] > d.y)
		{
			err[0] += d.y;
			a.x += s.x;
		}
		if (err[1] < d.x)
		{
			err[0] += d.x;
			a.y += s.y;
		}
	}
}
