/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:47:16 by juhan             #+#    #+#             */
/*   Updated: 2022/04/15 17:54:33 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_exit(t_map *m)
{
	free(m->map);
	mlx_destroy_image(m->mlx, m->img);
	mlx_destroy_window(m->mlx, m->win);
	exit(0);
}

void	close_fd_on_error(int fd)
{
	close(fd);
	exit(0);
}
