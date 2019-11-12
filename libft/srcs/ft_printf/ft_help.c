/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbessa <kbessa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 07:11:23 by kbessa            #+#    #+#             */
/*   Updated: 2019/11/04 20:35:25 by kbessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_len(const char *format)
{
	int i;

	i = 0;
	while (*format != '.' && *format != 'd' && *format != 's' && *format != 'i'
		&& *format != 'o' && *format != 'u' && *format != 'x' && *format != 'X'
		&& *format != 'c' && *format != 'p' && *format != 'f')
	{
		i++;
		format += 1;
	}
	return (i + 1);
}

int		dlwidth(long int a)
{
	int res;

	res = 0;
	while (a != 0)
	{
		a /= 10;
		res++;
	}
	return (res);
}

int		dlwidtho(unsigned long int a)
{
	int res;

	res = 0;
	if (a == 0)
		return (1);
	while (a != 0)
	{
		a /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa_base16(unsigned long int value, int base, int f)
{
	char	*ret;
	char	*tab_base;
	int		taille;
	int		i;

	tab_base = f == 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	if (value == 0)
		return ("0");
	taille = digit_count(value, base);
	if (!(ret = (char *)malloc(sizeof(char) * (taille + 1))))
		return (0);
	i = 1;
	while (value != 0)
	{
		ret[taille - i++] = tab_base[value % base];
		value /= base;
	}
	ret[taille] = '\0';
	return (ret);
}

int		dlwidthu(unsigned long int a)
{
	int res;

	res = 0;
	while (a != 0)
	{
		a /= 10;
		res++;
	}
	return (res);
}
