#include "fdf.h"
#include <stdio.h>

typedef struct s_map
{
	int		height;
	int		width;
	int		*map;

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
}

void	parse_map(t_map *m, int fd)
{
	char	*line;
	char	**split_res;
	char	**cpy;
	int		temp;
	int		i;

	m->map = malloc(m->height * m->width * sizeof(int));
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		printf("%s", line);
		
		split_res = ft_split(line, ' ');
		cpy = split_res;
		if (!split_res)
			exit(0);
		while (*split_res)
		{
			temp = ft_atoi(*split_res);
			m->map[i++] = temp;
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

void	draw_line(t_map *m, int a, int b, int c, int d)
{
	int	dx;
	int	dy;
	int	D;
	int	x;
	int	y;

	dx = c - a;
	dy = d - b;
	D = 2 * dy - dx;
	x = a;
	y = b;
	while (x <= c)
	{
		ft_mlx_pixel_put(m, x, y);
		if (D > 0)
		{
			y++;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
		x++;
	}

}

void	draw(t_map *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, 500, 500, "fdf");
	m->img = mlx_new_image(m->mlx, 500, 500);
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->line_length, &m->endian);

	ft_mlx_pixel_put(m, 300, 300);
	draw_line(m, 100, 100, 200, 200);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	mlx_loop(m->mlx);
}

int	main(int argc, char **argv)
{
	t_map	m;
	int		fd[2];

	(void)argc;
	fd[0] = open(argv[1], O_RDONLY);
	check_map(&m, fd[0]);
	fd[1] = open(argv[1], O_RDONLY);
	parse_map(&m, fd[1]);
	close(fd[0]);
	close(fd[1]);

	int i = 0;
	while (i < m.width * m.height)
	{
		printf("%2d ", m.map[i++]);
		if (i % m.width == 0)
			printf("\n");
	}
	draw(&m);
	return (0);
}