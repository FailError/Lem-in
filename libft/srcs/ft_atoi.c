/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:02:42 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/08 19:29:28 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void				atoi2(const char *str)
{
	int					len;
	int					j;

	j = 0;
	len = ft_strlen(str);
	while (len > 0)
	{
		if ((str[j] >= '0' && str[j] <= '9' && str[j + 1] != '-') ||
		(str[j] == '-' && str[j + 1] != '-'))
		{
			j++;
			len--;
		}
		else
		{
			ft_putstr("\x1B[31mError\033[0m\n");
			exit(0);
		}
	}
}

static void				atoi3(unsigned long res, int minus)
{
	if (res > INT_MAX && minus == 1)
	{
		ft_putstr("\x1B[31mError\033[0m\n");
		exit(0);
	}
	if (res > 2147483648 && minus == -1)
	{
		ft_putstr("\x1B[31mError\033[0m\n");
		exit(0);
	}
}

int						ft_atoi(const char *str)
{
	unsigned long int	res;
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
	atoi2(str);
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if(i == 20 && res == 0)
	{
		ft_putstr("\x1B[31mError\033[0m\n");
		exit(0);
	}
	atoi3(res, minus);
	return ((int)(res * minus));
}
