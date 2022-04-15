/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:47:16 by juhan             #+#    #+#             */
/*   Updated: 2022/04/15 15:50:14 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_projection(t_map *m)
{
	if (!m->is_iso)
		m->is_iso = 1;
	else
		m->is_iso = 0;
}

void	iso(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(M_PI / 6);
	*y = -z + (prev_x + prev_y) * sin(M_PI / 6);
}

t_coord	project(t_map *m, t_coord coord)
{
	coord.x *= m->tile_length * m->zoom;
	coord.y *= m->tile_length * m->zoom;
	coord.x -= m->camera_x_offset * m->zoom;
	coord.y -= m->camera_y_offset * m->zoom;
	coord.z *= m->z_val * m->zoom;
	rotate_x(&coord.y, &coord.z, m->angle_x);
	rotate_y(&coord.x, &coord.z, m->angle_y);
	rotate_z(&coord.x, &coord.y, m->angle_z);
	if (m->is_iso)
		iso(&coord.x, &coord.y, coord.z);
	coord.x += WIN_WIDTH / 2;
	coord.y += WIN_HEIGHT / 2;
	coord.x += m->translate_x;
	coord.y += m->translate_y;
	return (coord);
}
