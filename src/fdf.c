/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:47:16 by juhan             #+#    #+#             */
/*   Updated: 2022/04/15 18:03:09 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_width(t_map *m, char *line)
{
	char	**split_res;
	char	**cpy;

	split_res = ft_split(line, ' ');
	cpy = split_res;
	if (!split_res)
		return (0);
	while (*split_res)
	{
		split_res++;
		m->width++;
	}
	ft_free_all(cpy);
	return (1);
}

static void	check_map(t_map *m, int fd)
{
	char	*line;

	m->height = 0;
	m->width = 0;
	line = get_next_line(fd);
	if (!check_width(m, line))
		close_fd_on_error(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		m->height++;
	}
	if (m->width > m->height)
		m->tile_length = (WIN_WIDTH) / m->width;
	else
		m->tile_length = (WIN_HEIGHT) / m->height;
}

static int	parse_map_util(t_map *m, int fd)
{
	char	**split_res;
	char	**cpy;
	char	*line;
	int		i;
	int		temp;

	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		split_res = ft_split(line, ' ');
		cpy = split_res;
		if (!split_res)
			return (0);
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
	return (1);
}

static void	parse_map(t_map *m, int fd)
{
	m->map = malloc(m->height * m->width * sizeof(t_coord));
	if (!m->map)
		close_fd_on_error(fd);
	if (!parse_map_util(m, fd))
		close_fd_on_error(fd);
}

int	main(int argc, char **argv)
{
	t_map	m;
	int		fd[2];

	if (argc != 2)
	{
		ft_putstr_fd("usage: ./fdf [path to .fdf file]\n", 1);
		return (0);
	}
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[1], O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1)
	{
		ft_putstr_fd("Error: unable to open file\n", 1);
		return (0);
	}
	check_map(&m, fd[0]);
	parse_map(&m, fd[1]);
	close(fd[0]);
	close(fd[1]);
	set_coord(&m);
	draw(&m);
	return (0);
}
