#include "fdf.h"
#include <stdio.h>

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
