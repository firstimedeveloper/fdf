#include "fdf.h"
#include <stdio.h>

typedef struct 	s_coord
{
	int	x;
	int	y;
	int	z;
} t_coord;

typedef struct	s_map
{
	int		height;
	int		width;
	t_coord	*map;
	int		h_diff;
	int		w_diff;

	int		z_val;

	int		camera_x_offset;
	int		camera_y_offset;

	int		translate_x;
	int		translate_y;

	double	angle_x;
	double	angle_y;
	double	angle_z;

	double	zoom;

	void	*mlx;
	void	*win;

	void	*img;
	void	*addr;
	int		bpp;
	int		line_length;
	int		endian;
} t_map;

void	check_width(t_map *m, char *line)
{
	char	**split_res;
	char	**cpy;

	split_res = ft_split(line, ' ');
	cpy = split_res;
	if (!split_res)
		exit(0);
	while (*split_res)
	{
		split_res++;
		m->width++;
	}
	ft_free_all(cpy);
}

void	check_map(t_map *m, int fd)
{
	char	*line;
	int		max;

	m->height = 0;
	m->width = 0;
	line = get_next_line(fd);
	check_width(m, line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		m->height++;
	}
	if (m->width > m->height)
		max = m->width;
	else
		max = m->height;
	m->w_diff = (WIN_WIDTH) / max;
	m->h_diff = (WIN_HEIGHT) / max;
}

void	parse_map(t_map *m, int fd)
{
	char	*line;
	char	**split_res;
	char	**cpy;
	int		temp;
	int		i;

	m->map = malloc(m->height * m->width * sizeof(t_coord));
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		split_res = ft_split(line, ' ');
		cpy = split_res;
		if (!split_res)
			exit(0);
		while (*split_res)
		{
			temp = ft_atoi(*split_res);
			printf("%d ", temp);
			m->map[i++].z = temp;
			split_res++;
		}
		printf("\n");
		ft_free_all(cpy);
		free(line);
		line = get_next_line(fd);
	}
}

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

void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	set_coord(t_map *m)
{
	int	i;
	int	j;
	int	idx;

	i = 0;
	// printf("w_diff:%d h_diff:%d\n", m->w_diff, m->h_diff);
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			idx = i * m->width + j;
			// m->map[idx].x = m->w_diff * j;
			// m->map[idx].y = m->h_diff * i;
			m->map[idx].x = j;
			m->map[idx].y = i;
			j++;
		}
		i++;
	}
}

void	rotate_x(int *y, int *z, double angle)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(angle) + *z * sin(angle);
	*z = -prev_y * sin(angle) + *z * cos(angle);
}

void	rotate_y(int *x, int *z, double angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(angle) + *z * sin(angle);
	*z = -prev_x * sin(angle) + *z * cos(angle);
}

void	rotate_z(int *x, int *y, double angle)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(angle) - prev_y * sin(angle);
	*y = prev_x * sin(angle) + prev_y * cos(angle);
}

t_coord	project(t_map *m, t_coord coord)
{
	coord.x *= m->w_diff * m->zoom;
	coord.y *= m->h_diff * m->zoom;
	coord.x -= m->camera_x_offset;
	coord.y -= m->camera_y_offset;
	rotate_x(&coord.y, &coord.z, m->angle_x);
	rotate_y(&coord.x, &coord.z, m->angle_y);
	rotate_z(&coord.x, &coord.y, m->angle_z);
	coord.z *= m->z_val;
	iso(&coord.x, &coord.y, coord.z);
	coord.x += m->camera_x_offset;
	coord.y += m->camera_y_offset;
	coord.x += m->translate_x;
	coord.y += m->translate_y;
	return (coord);
}

void	draw_coord(t_map *m, int color)
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
			//printf("(%d,%d),", m->map[idx].x, m->map[idx].y);
			// printf("%d ", m->map[idx].z);
			if (j > 0)
				draw_line(m, project(m, m->map[idx - 1]), project(m, m->map[idx]), color);

			if (i > 0)
				draw_line(m, project(m, m->map[idx - m->width]), project(m, m->map[idx]), color);
		}
		// printf("\n");
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
	draw_coord(m, 0x808080);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	return (0);
}

int	handle_key(int key, t_map *m)
{
	printf("(%d)\n", key);
	switch (key)
	{
		case 53:
			exit(0);
			break;
		case 13:
			m->translate_y -= 10;
			break;
		case 0:
			m->translate_x -= 10;
			break;
		case 1:
			m->translate_y += 10;
			break;
		case 2:
			m->translate_x += 10;
			break;
		case 123:
			m->angle_x += M_PI / 45;
			break;
		case 124:
			m->angle_x -= M_PI / 45;
			break;
		case 126:
			m->angle_y += M_PI / 45;
			break;
		case 125:
			m->angle_y -= M_PI / 45;
			break;
		case 12:
			m->angle_z += M_PI / 45;
			break;
		case 14:
			m->angle_z -= M_PI / 45;
			break;
		case 27:
			m->zoom -= 0.1;
			break;
		case 24:
			m->zoom += 0.1;
			break;
		case 43:
			m->z_val -= 1;
			break;
		case 47:
			m->z_val += 1;
			break;
	}
	render_frame(m);
	return (0);
}

void	draw(t_map *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	m->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->line_length, &m->endian);
	m->camera_x_offset = (m->width / 2) * m->w_diff;
	m->camera_y_offset = (m->height / 2) * m->h_diff;
	m->translate_x = 0;
	m->translate_y = 0;
	m->angle_x = 0;
	m->angle_y = 0;
	m->angle_z = 0;
	m->z_val = 1;
	m->zoom = 1;

	render_frame(m);
	//mlx_key_hook(m->win, handle_key, m);
	mlx_hook(m->win, 2, 0, handle_key, m);
	//mlx_loop_hook(m->mlx, render_frame, m);
}

int	main(int argc, char **argv)
{
	t_map	m;
	int		fd[2];

	if (argc != 2)
	{
		ft_putstr_fd("usage: ./fdf [path to .fdf file]\n", 1);
		return(0);
	}
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[1], O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1)
	{
		ft_putstr_fd("Error: unable to open file\n", 1);
		return(1);
	}
	check_map(&m, fd[0]);
	parse_map(&m, fd[1]);
	close(fd[0]);
	close(fd[1]);

	printf("w: %d h: %d\n", m.width, m.height);
	set_coord(&m);
	draw(&m);
	mlx_loop(m.mlx);
	return (0);
}
