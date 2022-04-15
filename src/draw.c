/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:47:16 by juhan             #+#    #+#             */
/*   Updated: 2022/04/15 16:23:34 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	mlx_hook(m->win, 2, 0, handle_key, m);
	mlx_hook(m->win, 17, 0, handle_exit, m);
	mlx_loop(m->mlx);
}
