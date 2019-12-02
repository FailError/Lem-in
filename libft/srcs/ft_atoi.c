/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:02:42 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/28 18:59:13 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					ft_error1(void)
{
	ft_putstr("\x1B[31mError\033[0m\n");
	exit(-1);
}

static void				atoi3(long long res, int minus)
{
	if (res > INT_MAX && minus == 1)
	{
		ft_putstr("\x1B[31mError\033[0m\n");
		exit(0);
	}
	else if (res >= 0 && minus == -1)
	{
		ft_putstr("\x1B[31mError\033[0m\n");
		exit(0);
	}
	else if (res == 0)
		ft_error1();
}

int						ft_atoi(const char *str)
{
	long long int	res;
	int					minus;
	size_t				i;

	res = 0;
	minus = 1;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if((i == 20 && res == 0) || (str[i] && !(str[i] >= '0' && str[i] <= '9')))
		ft_error1();
	atoi3(res, minus);
	return ((int)(res * minus));
}
