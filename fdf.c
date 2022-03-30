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
	m->w_diff = (WIN_WIDTH - 100) / max;
	m->h_diff = (WIN_HEIGHT - 100) / max;
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
			m->map[i++].z = temp;
			split_res++;
		}
		ft_free_all(cpy);
		free(line);
		line = get_next_line(fd);
	}
}

void	ft_mlx_pixel_put(t_map *m, int x, int y)
{
	char	*dst;

	dst = m->addr + (y * m->line_length + x * (m->bpp / 8));
	*(unsigned int*)dst = 0xFFFFFFFF;
}

void draw_line(t_map *m, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (1)
	{
		ft_mlx_pixel_put(m, x0, y0);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			if (x0 == x1)
				break ;
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			if (y0 == y1)
				break ;
			err += dx;
			y0 += sy;
		}
	}

//   int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
//   int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
//   int err = (dx>dy ? dx : -dy)/2, e2;

//   for(;;){
//     ft_mlx_pixel_put(m, x0,y0);   //color the pixel in the matrix for later use.
//     if (x0==x1 && y0==y1) break;
//     e2 = err;
//     if (e2 >-dx) { err -= dy; x0 += sx; }
//     if (e2 < dy) { err += dx; y0 += sy; }
//   }
}

// void	draw_line(t_map *m, int a, int b, int c, int d)
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
// 		ft_mlx_pixel_put(m, x, y);
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

void	draw(t_map *m)
{
	int	i;
	int	j;
	int	idx;

	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	m->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->line_length, &m->endian);

	printf("w: %d h: %d\n", m->width, m->height);

	i = -1;
	while (++i < m->height)
	{
		j = -1;
		while (++j < m->width)
		{
			idx = i * m->width + j;
			printf("(%d,%d),", m->map[idx].x, m->map[idx].y);
			if (j > 0)
				draw_line(m, m->map[idx - 1].x, m->map[idx - 1].y, m->map[idx].x, m->map[idx].y);
			if (i > 0)
				draw_line(m, m->map[idx - m->width].x, m->map[idx - m->width].y, m->map[idx].x, m->map[idx].y);
		}
		printf("\n");
	}
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	mlx_loop(m->mlx);
}

void	set_coord(t_map *m)
{
	int	i;
	int	j;
	int	idx;

	i = 0;
	printf("w_diff:%d h_diff:%d\n", m->w_diff, m->h_diff);
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{

			idx = i * m->width + j;
			m->map[idx].x = m->w_diff * j;
			m->map[idx].y = m->h_diff * i;
			iso(&m->map[idx].x, &m->map[idx].y, m->map[idx].z);
			j++;
		}
		i++;
	}
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
	return (0);
}
