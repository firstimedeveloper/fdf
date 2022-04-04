#include "fdf.h"

void	set_projection(t_map *m)
{
	if (!m->is_ISO)
		m->is_ISO = 1;
	else
		m->is_ISO = 0;
}

void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

t_coord	project(t_map *m, t_coord coord)
{
	coord.x *= m->w_diff * m->zoom;
	coord.y *= m->h_diff * m->zoom;
	coord.x -= m->camera_x_offset * m->zoom;
	coord.y -= m->camera_y_offset * m->zoom;
	coord.z *= m->z_val;
	rotate_x(&coord.y, &coord.z, m->angle_x);
	rotate_y(&coord.x, &coord.z, m->angle_y);
	rotate_z(&coord.x, &coord.y, m->angle_z);
	if (m->is_ISO)
		iso(&coord.x, &coord.y, coord.z);
	coord.x += m->camera_x_offset;
	coord.y += m->camera_y_offset;
	coord.x += m->translate_x;
	coord.y += m->translate_y;
	return (coord);
}
