/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 16:44:04 by juhan             #+#    #+#             */
/*   Updated: 2022/03/23 15:19:43 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
				s++;
			count++;
		}
		else
			s++;
	}
	return (count);
}

static size_t	ft_strclen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s == c)
			break ;
		s++;
		len++;
	}
	return (len);
}

char	**ft_free_all(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

static char	**init(char const *s, char c, size_t *len)
{
	char	**ret;

	if (!s)
		return (0);
	*len = ft_count_words(s, c);
	ret = malloc(sizeof(char *) * (*len + 1));
	if (!ret)
		return (0);
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**ret;
	size_t	word_len;
	size_t	i;

	ret = init(s, c, &len);
	i = 0;
	while (*s && i < len)
	{
		if (*s != c)
		{
			word_len = ft_strclen(s, c);
			ret[i] = malloc(sizeof(char) * (word_len + 1));
			if (!ret[i])
				return (ft_free_all(ret));
			ft_memccpy(ret[i], s, c, word_len);
			ret[i++][word_len] = '\0';
			s += word_len;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}
