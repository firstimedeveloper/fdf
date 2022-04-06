#include "fdf.h"

void	set_coord(t_map *m)
{
	int	i;
	int	j;
	int	idx;

	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			idx = i * m->width + j;
			m->map[idx].x = j;
			m->map[idx].y = i;
			j++;
		}
		i++;
	}
}

void	init_map(t_map *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	m->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->line_length, &m->endian);
	m->camera_x_offset = (m->width / 2) * m->tile_length;
	m->camera_y_offset = (m->height / 2) * m->tile_length;
	m->translate_x = 0;
	m->translate_y = 0;
	m->angle_x = 0;
	m->angle_y = 0;
	m->angle_z = 0;
	m->z_val = 1;
	m->zoom = 0.8;
	m->is_ISO = 1;
}
