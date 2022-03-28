/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:52:13 by juhan             #+#    #+#             */
/*   Updated: 2022/03/28 19:45:50 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	err(void)
{
	ft_putstr_fd("Error", 1);
	exit(-1);
}

int	ft_atoi(const char *str)
{
	long int	val;
	int			neg;

	val = 0;
	neg = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str && (ft_isdigit(*str) || *str == '\n'))
	{
		if (*str == '\n')
		{
			str++;
			break ;
		}
		val *= 10;
		val += *str - '0';
		str++;
	}
	val *= neg;
	if (val < -2147483648 || val > 2147483647 || *str)
		err();
	return (val);
}
