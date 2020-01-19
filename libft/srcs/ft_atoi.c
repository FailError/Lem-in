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

void					error(char *str)
{
	ft_printf("\x1B[31mError, \033[0m", str);
	ft_printf("\x1B[31m%s\033[0m\n", str);
	exit(-1);
}

void					check_res_only_int(char *str, int i, int minus,
						long long res)
{
	if (i > 11)
	{
		ft_printf("\x1B[31mInvalid coord: [%s is a %s]\033[0m\n",
			str, "Long number");
		exit(1);
	}
	if (res > 2147483647l && minus == 1)
	{
		ft_printf("\x1B[31mInvalid coord: [%s %s]\033[0m\n",
			str, "more than INT_MAX");
		exit(1);
	}
	if (res > 2147483648l && minus == -1)
	{
		ft_printf("\x1B[31mInvalid coord: [%s %s]\033[0m\n",
			str, "more than INT_MIN");
		exit(1);
	}
}

void					result(const char *str, long long *res, size_t *i)
{
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		*res = (*res * 10) + str[*i] - '0';
		*i += 1;
	}
	else
		error("Please, enter valid coord [0-9]!");
}

int						ft_atoi(char *str)
{
	long long int		res;
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
	while (str[i])
		result(str, &res, &i);
	check_res_only_int(str, i, minus, res);
	free(str);
	return ((int)(res * minus));
}
