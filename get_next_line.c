/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:39:56 by juhan             #+#    #+#             */
/*   Updated: 2021/07/29 01:35:50 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_all(char **save)
{
	free(*save);
	*save = 0;
}

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			break ;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

static char	*save_str(char **save)
{
	char	*ret;
	char	*temp;
	int		len;

	len = 0;
	while ((*save)[len] != '\n' && (*save)[len] != '\0')
		len++;
	if ((*save)[len] == '\n')
	{
		ret = ft_substr(*save, 0, len + 1);
		temp = ft_strdup(&((*save)[len + 1]));
		free(*save);
		*save = temp;
		if ((*save)[0] == '\0')
			free_all(save);
	}
	else
	{
		ret = ft_strdup(*save);
		free_all(save);
	}
	return (ret);
}

static char	*return_str(int fd, char **save)
{
	if (!save[fd])
		return (0);
	else
		return (save_str(&save[fd]));
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*temp;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (0);
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		if (!save[fd])
			save[fd] = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(save[fd], buf);
			free(save[fd]);
			save[fd] = temp;
		}
		if (!save[fd] || ft_strchr(save[fd], '\n'))
			break ;
	}
	return (return_str(fd, save));
}
